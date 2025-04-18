/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:05:46 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/18 12:58:35 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	print_external_path_error(t_command *cmd, char *cmd_path)
{
	char	*fmt;
	int		exit_code;

	fmt = format_token(cmd->args[0]);
	perror(fmt);
	exit_code = get_exit_code_by_errno();
	free(fmt);
	free(cmd_path);
	free_command(cmd);
	exit(exit_code);
}

static void	external_path_failure(t_command *cmd,
	char *cmd_path, t_plchild_data *d)
{
	char	*fmt;
	int		i;

	fmt = format_token(cmd->args[0]);
	write(STDERR_FILENO, fmt, ft_strlen(fmt));
	write(STDERR_FILENO, ": command not found\n", 20);
	free(fmt);
	free(cmd_path);
	i = 0;
	while (d->cmds[i])
	{
		free_command(d->cmds[i]);
		i++;
	}
	free(d->cmds);
	close(0);
	close(1);
	exit(127);
}

void	handle_external_path(t_command *cmd,
	char *cmd_path, t_plchild_data *d, t_shell *shell)
{
	char	**new_env;

	new_env = build_envp(shell, cmd_path);
	if (!new_env)
		external_path_failure(cmd, cmd_path, d);
	execve(cmd_path, cmd->args, new_env);
	free_envp(new_env);
	free_envp(shell->envp);
	shell->envp = NULL;
	check_if_directory(cmd, cmd_path);
	print_external_path_error(cmd, cmd_path);
}

static void	handle_external_command_exec(t_pipeline_child *pc,
	t_plchild_data *d, t_shell *shell, char *cmd_path)
{
	char	**envp;

	(void)d;
	envp = build_envp(shell, cmd_path);
	execve(cmd_path, pc->cmd->args, envp);
	perror("execve");
	free_envp(envp);
	free(cmd_path);
	free_command(pc->cmd);
	exit(1);
}

void	handle_external_command(t_pipeline_child *pc,
	t_plchild_data *d, t_shell *shell)
{
	char	*cmd_path;
	int		i;

	cmd_path = find_command_path(shell, pc->cmd->args[0]);
	if (!cmd_path)
	{
		if (shell->envp)
		{
			free_envp(shell->envp);
			shell->envp = NULL;
		}
		handle_cmd_not_found(pc->cmd, d);
		free_command(pc->cmd);
		i = 0;
		while (d->cmds[i])
			free_command(d->cmds[i++]);
		free(d->cmds);
		close(0);
		close(1);
		exit(127);
	}
	handle_external_command_exec(pc, d, shell, cmd_path);
}
