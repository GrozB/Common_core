#include "minitalk.h"

volatile sig_atomic_t g_acknowledged = 0;

void	acknowledge_signal(int sig)
{
    (void)sig;
    g_acknowledged = 1;
}

void	send_bit(pid_t pid, char bit)
{
    int signal;

    if (bit == 1)
        signal = SIGUSR1;
    else
        signal = SIGUSR2;
    if (kill(pid, signal) == -1)
    {
        write(2, "Error: Failed to send signal\n", 29);
        exit(EXIT_FAILURE);
    }
    while (!g_acknowledged)
        ;
    g_acknowledged = 0;
}

void	send_size(pid_t pid, size_t size)
{
    int bit;

    bit = sizeof(size_t) * 8 - 1;
    while (bit >= 0)
    {
        send_bit(pid, (size >> bit) & 1);
        bit--;
    }
}

void	send_char(pid_t pid, char c)
{
    int bit;

    bit = 7;
    while (bit >= 0)
    {
        send_bit(pid, (c >> bit) & 1);
        bit--;
    }
}

void	send_message(pid_t pid, const char *message)
{
    size_t size;
    int i;

    size = ft_strlen(message);
    send_size(pid, size);
    i = 0;
    while (message[i])
    {
        send_char(pid, message[i]);
        i++;
    }
}

int	main(int argc, char **argv)
{
    pid_t pid;

    if (argc != 3)
    {
        ft_printf("Usage: %s <PID> <message>\n", argv[0]);
        return (1);
    }
    pid = ft_atoi(argv[1]);
    if (pid <= 0)
    {
        ft_printf("Invalid PID: %s\n", argv[1]);
        return (1);
    }
    signal(SIGUSR2, acknowledge_signal);
    send_message(pid, argv[2]);
    return (0);
}