/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:32:30 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/10 18:06:26 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_global;

void	acknowledge_signal(int sig)
{
	(void)sig;
	g_global = 1;
}

void	send_bit(pid_t pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if ((c >> bit) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		g_global = 0;
		while (!g_global)
			pause();
		bit--;
	}
}

void	send_message(pid_t pid, char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		send_bit(pid, msg[i]);
		i++;
	}
	send_bit(pid, '\0');
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		write(1, "Number of arguments is not correct\n", 36);
		return (1);
	}
	pid = atoi(argv[1]);
	signal(SIGUSR1, acknowledge_signal);
	send_message(pid, argv[2]);
	return (0);
}
