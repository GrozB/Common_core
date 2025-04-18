/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_missing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:03:27 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/15 16:08:06 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	handle_missing_path_exec(t_command *cmd, t_shell *shell)
{
	char	**new_env;

	new_env = build_envp(shell, cmd->args[0]);
	execve(cmd->args[0], cmd->args, new_env);
	free_envp(new_env);
	if (shell->envp)
	{
		free_envp(shell->envp);
		shell->envp = NULL;
	}
}

static void	handle_missing_path_error(t_command *cmd)
{
	char	*fmt;
	int		exit_code;

	fmt = format_token(cmd->args[0]);
	print_error_message(fmt);
	exit_code = get_exit_code_by_errno();
	free(fmt);
	free_command(cmd);
	exit(exit_code);
}

static void	handle_missing_path(t_command *cmd, t_shell *shell)
{
	handle_missing_path_exec(cmd, shell);
	handle_missing_path_error(cmd);
}

void	handle_cmd_not_found(t_command *cmd, t_plchild_data *d)
{
	char	*fmt;
	int		i;

	fmt = format_token(cmd->args[0]);
	err_msg(fmt, "command not found");
	free(fmt);
	i = 0;
	if (d && d->cmds)
	{
		while (d->cmds[i])
		{
			free_command(d->cmds[i]);
			i++;
		}
		free(d->cmds);
	}
	else
		free_command(cmd);
	close(0);
	close(1);
	exit(127);
}

void	handle_external_no_path(t_command *cmd,
	t_plchild_data *d, t_shell *shell)
{
	char	*path_env;

	path_env = my_getenv(shell, "PATH");
	if (!ft_strchr(cmd->args[0], '/') && (!path_env || !*path_env))
		handle_missing_path(cmd, shell);
	else
	{
		if (shell->envp)
		{
			free_envp(shell->envp);
			shell->envp = NULL;
		}
		handle_cmd_not_found(cmd, d);
	}
}
