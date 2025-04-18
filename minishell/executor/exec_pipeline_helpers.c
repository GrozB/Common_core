/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:07:24 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 20:13:03 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	pipeline_child_setup(t_pipeline_child *pc,
	t_plchild_data *d, t_shell *shell)
{
	if (pc->prev_fd != -1)
	{
		dup2(pc->prev_fd, STDIN_FILENO);
		close(pc->prev_fd);
	}
	if (pc->index < pc->count - 1)
	{
		close(pc->pipe_fd[0]);
		dup2(pc->pipe_fd[1], STDOUT_FILENO);
		close(pc->pipe_fd[1]);
	}
	apply_redirections(pc->cmd, d, shell);
}

static void	handle_empty_command(t_pipeline_child *pc)
{
	if (pc->cmd->args[0] == NULL)
	{
		free_command(pc->cmd);
		exit(0);
	}
}

static void	handle_builtin_command(t_pipeline_child *pc,
	t_plchild_data *d, t_shell *shell)
{
	int	ret;
	int	i;

	if (is_builtin(pc->cmd->args[0]))
	{
		ret = execute_builtin(pc->cmd, d, shell);
		i = 0;
		while (d->cmds[i])
		{
			free_command(d->cmds[i]);
			i++;
		}
		free(d->cmds);
		if (shell->envp)
		{
			free_envp(shell->envp);
			shell->envp = NULL;
		}
		close(0);
		close(1);
		exit(ret);
	}
}

static void	handle_builtin_or_empty_command(t_pipeline_child *pc,
	t_plchild_data *d, t_shell *shell)
{
	handle_empty_command(pc);
	handle_builtin_command(pc, d, shell);
}

void	pipeline_child_proc(t_pipeline_child *pc,
	t_plchild_data *d, t_shell *shell)
{
	pipeline_child_setup(pc, d, shell);
	if (pc->pids)
		free(pc->pids);
	handle_builtin_or_empty_command(pc, d, shell);
	handle_external_command(pc, d, shell);
}
