/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:02:39 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/16 15:17:17 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	external_child_proc(t_command *cmd,
	t_plchild_data *d, t_shell *shell)
{
	char	*cmd_path;

	apply_redirections(cmd, d, shell);
	cmd_path = find_command_path(shell, cmd->args[0]);
	if (!cmd_path)
		handle_external_no_path(cmd, d, shell);
	else
		handle_external_path(cmd, cmd_path, NULL, shell);
}

static void	setup_sigaction_handler(struct sigaction *old, void (*handler)(int))
{
	struct sigaction	temp;

	temp.sa_handler = handler;
	sigemptyset(&temp.sa_mask);
	temp.sa_flags = 0;
	sigaction(SIGINT, &temp, old);
}

static int	exec_external_command(t_command *cmd,
	t_plchild_data *d, t_shell *shell)
{
	pid_t				pid;
	int					status;
	struct sigaction	old_action;

	setup_sigaction_handler(&old_action, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		sigaction(SIGINT, &old_action, NULL);
		return (1);
	}
	if (pid == 0)
	{
		handle_external_command_signals();
		external_child_proc(cmd, d, shell);
	}
	wait_for_external_command(pid, &status);
	sigaction(SIGINT, &old_action, NULL);
	close_heredoc_fds(cmd);
	return (exit_status(status));
}

static int	exec_empty_command(t_command *cmd,
	t_plchild_data *d, t_shell *shell)
{
	pid_t				pid;
	int					status;
	struct sigaction	old;

	setup_sigaction_handler(&old, sigint_print_handler);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		sigaction(SIGINT, &old, NULL);
		status = 1;
	}
	else if (pid == 0)
	{
		apply_redirections(cmd, d, shell);
		free_command(cmd);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		sigaction(SIGINT, &old, NULL);
		close_heredoc_fds(cmd);
	}
	return (exit_status(status));
}

int	execute_command(t_command *cmd, t_shell *shell, t_plchild_data *d)
{
	(void)shell;
	if (cmd == NULL || cmd->args == NULL)
		return (0);
	if (cmd->args[0] == NULL)
		return (exec_empty_command(cmd, d, shell));
	if (is_builtin(cmd->args[0]))
		return (exec_builtin_command(cmd, shell, d));
	return (exec_external_command(cmd, d, shell));
}
