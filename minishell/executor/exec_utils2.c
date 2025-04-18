/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:29:46 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/16 15:21:00 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	sigint_print_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	handle_external_command_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	wait_for_external_command(pid_t pid, int *status)
{
	int		sig;

	waitpid(pid, status, 0);
	if (WIFSIGNALED(*status))
	{
		sig = WTERMSIG(*status);
		if (sig == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
		}
		else if (sig == SIGQUIT)
		{
			if (WCOREDUMP(*status))
				write(STDERR_FILENO, "Quit (core dumped)\n", 20);
			else
				write(STDERR_FILENO, "Quit\n", 5);
		}
	}
}
