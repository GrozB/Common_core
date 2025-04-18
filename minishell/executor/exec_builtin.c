/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:55:15 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 16:16:01 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "exit") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_command *cmd, t_plchild_data *d, t_shell *shell)
{
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (builtin_exit(cmd->args, d, shell));
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (builtin_cd(shell, cmd->args));
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (builtin_echo(cmd->args));
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (builtin_env(shell));
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (builtin_export(shell, cmd->args));
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (builtin_unset(shell, cmd->args));
	return (1);
}

int	exec_builtin_command(t_command *cmd,
	t_shell *shell, t_plchild_data *d)
{
	int	saved_in;
	int	saved_out;
	int	status;

	if (handle_builtin_redirection(cmd, &saved_in, &saved_out))
		return (1);
	if (ft_strcmp(cmd->args[0], "exit") == 0)
	{
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		builtin_exit(cmd->args, d, shell);
		return (0);
	}
	else
	{
		status = execute_builtin(cmd, d, shell);
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		return (status);
	}
}

static int	redirect_for_builtin(t_command *cmd, int saved_in, int saved_out)
{
	int	i;

	i = 0;
	while (i < cmd->nb_redirs)
	{
		if (single_redir(&cmd->redirs[i], saved_in, saved_out))
			return (1);
		i++;
	}
	return (0);
}

int	handle_builtin_redirection(t_command *cmd,
	int *saved_in, int *saved_out)
{
	*saved_in = dup(STDIN_FILENO);
	*saved_out = dup(STDOUT_FILENO);
	if (redirect_for_builtin(cmd, *saved_in, *saved_out))
	{
		close(*saved_in);
		close(*saved_out);
		return (1);
	}
	return (0);
}
