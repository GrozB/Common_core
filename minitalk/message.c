/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:51:35 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/21 18:03:23 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_acknowledged = 0;

void	acknowledge_signal(int sig)
{
	(void)sig;
	g_acknowledged = 1;
}

void	send_bit(pid_t pid, char bit)
{
	int	signal;

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
	int	bit;

	bit = sizeof(size_t) * 8 - 1;
	while (bit >= 0)
	{
		send_bit(pid, (size >> bit) & 1);
		bit--;
	}
}

void	send_char(pid_t pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		send_bit(pid, (c >> bit) & 1);
		bit--;
	}
}

void	send_message(pid_t pid, const char *message)
{
	size_t	size;
	int		i;

	size = ft_strlen(message);
	send_size(pid, size);
	i = 0;
	while (message[i])
	{
		send_char(pid, message[i]);
		i++;
	}
}
