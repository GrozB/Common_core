/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:03:48 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/10 18:12:34 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	append_char_to_string(char **str, char c, int *len)
{
	char	*new_str;
	int		i;

	new_str = malloc(*len + 2);
	if (*str != NULL)
	{
		i = 0;
		while (i < *len)
		{
			new_str[i] = (*str)[i];
			i++;
		}
		free(*str);
	}
	new_str[*len] = c;
	new_str[*len + 1] = '\0';
	*str = new_str;
	(*len)++;
}

void	reset_and_print(char **str, int *len)
{
	if (*str != NULL)
	{
		write(1, *str, *len);
		free(*str);
		*str = NULL;
		*len = 0;
	}
}

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int		bit_count;
	static char		c;
	static char		*str;
	static int		len;
	pid_t			client_pid;

	(void)context;
	client_pid = info->si_pid;
	c <<= 1;
	if (sig == SIGUSR1)
		c |= 1;
	bit_count++;
	if (bit_count == 8)
	{
		if (c != '\0')
			append_char_to_string(&str, c, &len);
		else
			reset_and_print(&str, &len);
		reset_static_vars(&bit_count, &c);
	}
	send_acknowledgment(client_pid);
}

void	init_server(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}

int	main(void)
{
	pid_t	pid;
	char	pid_str[20];
	int		i;
	int		n;

	pid = getpid();
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
	init_server();
	return (0);
}
