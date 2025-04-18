/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_fork.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:10:26 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 16:25:50 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	setup_pipe_and_fork(t_plchild_data *d)
{
	if (d->index < d->count - 1 && pipe(d->pipe_fd) < 0)
	{
		perror("pipe");
		return (1);
	}
	*(d->child_pid) = fork();
	if (*(d->child_pid) < 0)
	{
		perror("fork");
		if (d->index < d->count - 1)
		{
			close(d->pipe_fd[0]);
			close(d->pipe_fd[1]);
		}
		return (1);
	}
	return (0);
}

static void	child_proc_pipeline(t_plchild_data *d, t_shell *shell)
{
	t_pipeline_child	pc;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	pc.cmd = d->cmd;
	pc.index = d->index;
	pc.count = d->count;
	pc.prev_fd = d->prev_fd;
	pc.pipe_fd[0] = d->pipe_fd[0];
	pc.pipe_fd[1] = d->pipe_fd[1];
	pc.pids = d->pids;
	pipeline_child_proc(&pc, d, shell);
}

static void	parent_proc_pipeline(t_plchild_data *d)
{
	if (d->prev_fd != -1)
		close(d->prev_fd);
	if (d->index < d->count - 1)
	{
		close(d->pipe_fd[1]);
		*(d->new_prev_fd) = d->pipe_fd[0];
	}
	else
		*(d->new_prev_fd) = -1;
	close_heredoc_fds_pipeline(d->cmd);
}

int	launch_pipeline_child(t_plchild_data *d, t_shell *shell)
{
	if (setup_pipe_and_fork(d) != 0)
	{
		*(d->new_prev_fd) = d->prev_fd;
		return (1);
	}
	if (*(d->child_pid) == 0)
		child_proc_pipeline(d, shell);
	else
		parent_proc_pipeline(d);
	return (0);
}

int	init_pipeline_children(pid_t **pids, int n, int *prev_fd)
{
	*pids = ft_calloc(n, sizeof(pid_t));
	if (!(*pids))
		return (1);
	*prev_fd = -1;
	return (0);
}
