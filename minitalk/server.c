#include "minitalk.h"

volatile sig_atomic_t g_bit_received = 0;

void reset_state(int *bit_count, size_t *size, size_t *received, char **message, int *state, unsigned char *c) {
    *bit_count = 0;
    *size = 0;
    *received = 0;
    free(*message);
    *message = NULL;
    *state = 0;
    *c = 0;
}

void handle_signal(int sig, siginfo_t *info, void *context) {
    static int bit_count = 0;
    static size_t size = 0;
    static size_t received = 0;
    static char *message = NULL;
    static int state = 0; // 0: receiving size, 1: receiving message
    static unsigned char c = 0;

    (void)context;
    if (sig == SIGUSR1)
        c |= (1 << (7 - bit_count));
    bit_count++;
    if (bit_count == 8) {
        if (state == 0) {
            size = (size << 8) | c;
            if (++received == sizeof(size_t)) {
                message = (char *)malloc(size + 1);
                if (!message)
                    exit(EXIT_FAILURE);
                message[size] = '\0';
                state = 1;
                received = 0;
            }
        } else {
            message[received++] = c;
            if (received == size) {
                write(1, message, size);
                write(1, "\n", 1);
                reset_state(&bit_count, &size, &received, &message, &state, &c);
            }
        }
        bit_count = 0;
        c = 0;
    }
    g_bit_received = 1;
    kill(info->si_pid, SIGUSR2);
}

int main(void) {
    pid_t pid;
    struct sigaction sa;

    pid = getpid();
    ft_printf("Server PID: %d\n", pid);
    sa.sa_sigaction = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1) {
        ft_printf("Error setting up signal handlers\n");
        exit(EXIT_FAILURE);
    }
    while (1) {
        pause();
        if (g_bit_received) {
            g_bit_received = 0;
            // Process accumulated bits if needed
        }
    }
    return 0;
}