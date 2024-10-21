/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:01:27 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/21 17:22:06 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_bit_received = 0;

void	reset_state(t_message *msg)
{
	msg->bit_count = 0;
	msg->size = 0;
	msg->received = 0;
	free(msg->message);
	msg->message = NULL;
	msg->state = 0;
	msg->c = 0;
}

void	handle_bit(int sig, t_message *msg)
{
	if (sig == SIGUSR1)
	{
		msg->c |= (1 << (7 - msg->bit_count));
	}
	msg->bit_count++;
}

void	handle_message(t_message *msg)
{
	if (msg->state == 0)
	{
		msg->size = (msg->size << 8) | msg->c;
		if (++msg->received == sizeof(size_t))
		{
			msg->message = (char *)malloc(msg->size + 1);
			if (!msg->message)
			{
				exit(EXIT_FAILURE);
			}
			msg->message[msg->size] = '\0';
			msg->state = 1;
			msg->received = 0;
		}
	}
	else
	{
		msg->message[msg->received++] = msg->c;
		if (msg->received == msg->size)
		{
			write(1, msg->message, msg->size);
			write(1, "\n", 1);
			reset_state(msg);
		}
	}
}

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static t_message	msg = {0, 0, 0, NULL, 0, 0};

	(void)context;
	handle_bit(sig, &msg);
	if (msg.bit_count == 8)
	{
		handle_message(&msg);
		msg.bit_count = 0;
		msg.c = 0;
	}
	g_bit_received = 1;
	kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Error setting up signal handlers\n");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		pause();
		if (g_bit_received)
		{
			g_bit_received = 0;
		}
	}
	return (0);
}
