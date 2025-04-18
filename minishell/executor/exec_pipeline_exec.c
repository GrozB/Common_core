/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:11:24 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 16:11:46 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	check_pipeline_child(t_plchild_data *d, pid_t *pids, t_shell *shell)
{
	if (launch_pipeline_child(d, shell) != 0)
	{
		free(pids);
		return (1);
	}
	return (0);
}

static int	pipeline_children_loop(t_command **cmds,
	int n, t_pipeline_exec *pe, t_shell *shell)
{
	int				i;
	int				new_prev_fd;
	t_plchild_data	d;

	i = 0;
	new_prev_fd = -1;
	while (i < n)
	{
		d.cmd = cmds[i];
		d.cmds = cmds;
		d.index = i;
		d.count = n;
		d.prev_fd = *(pe->prev_fd);
		d.new_prev_fd = &new_prev_fd;
		d.child_pid = &pe->pids[i];
		d.pipe_fd[0] = -1;
		d.pipe_fd[1] = -1;
		d.pids = pe->pids;
		if (check_pipeline_child(&d, pe->pids, shell))
			return (1);
		*(pe->prev_fd) = new_prev_fd;
		i++;
	}
	return (0);
}

static int	execute_pipeline_children(t_command **cmds,
	int n, pid_t **pids_ptr, t_shell *shell)
{
	int				prev_fd;
	pid_t			*pids;
	t_pipeline_exec	pe;

	*pids_ptr = NULL;
	pids = NULL;
	if (init_pipeline_children(&pids, n, &prev_fd) != 0)
	{
		*pids_ptr = NULL;
		return (1);
	}
	pe.pids = pids;
	pe.prev_fd = &prev_fd;
	if (pipeline_children_loop(cmds, n, &pe, shell) != 0)
	{
		*pids_ptr = NULL;
		return (1);
	}
	*pids_ptr = pids;
	return (0);
}

static int	wait_for_pipeline_children(t_command **cmds, int n, pid_t *pids)
{
	int	i;
	int	status;

	(void)cmds;
	ft_bzero(&status, sizeof(int));
	waitpid(pids[n - 1], &status, 0);
	i = 0;
	while (i < n - 1)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	free(pids);
	return (exit_status(status));
}

int	execute_pipeline(t_command **cmds, int n, t_shell *shell)
{
	pid_t				*pids;
	struct sigaction	old;
	struct sigaction	temp;
	int					ret;

	(void)shell;
	pids = NULL;
	temp.sa_handler = sigint_print_handler;
	sigemptyset(&temp.sa_mask);
	temp.sa_flags = 0;
	sigaction(SIGINT, &temp, &old);
	if (execute_pipeline_children(cmds, n, &pids, shell) != 0)
	{
		sigaction(SIGINT, &old, NULL);
		if (pids)
			free(pids);
		return (1);
	}
	ret = wait_for_pipeline_children(cmds, n, pids);
	sigaction(SIGINT, &old, NULL);
	return (ret);
}
