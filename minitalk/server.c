#include "minitalk.h"

void	handle_signal(int sig)
{
	static int	bit_count = 0;
	static char	c = 0;

	c <<= 1;
	if (sig == SIGUSR1)
		c |= 1;
	bit_count++;
	if (bit_count == 8)
	{
		if (c != '\0')
			write(1, &c, 1);
		bit_count = 0;
		c = 0;
	}
}

int	main(void)
{
	pid_t	pid;
	char	pid_str[20];
	int		i;
	int		n;

	pid = getpid();
	write(1, "Server PID: ", 12);
	n = pid;
	i = 0;
	while (n > 0)
	{
		pid_str[i++] = (n % 10) + '0';
		n /= 10;
	}
	while (i--)
		write(1, &pid_str[i], 1);
	write(1, "\n", 1);
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while (1)
		pause();
	return (0);
}
