/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:32:56 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/18 13:04:07 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

int	handle_pipeline_execution(char **tokens, t_shell *shell)
{
	t_command	**cmds;
	int			num_commands;
	int			status;
	int			i;

	ft_bzero(&num_commands, sizeof(int));
	cmds = split_commands(tokens, &num_commands,
			shell->last_exit_status, shell);
	if (!cmds)
	{
		i = 0;
		while (tokens[i])
			free(tokens[i++]);
		free(tokens);
		shell->last_exit_status = 2;
		return (2);
	}
	free_str_array(tokens);
	status = execute_pipeline(cmds, num_commands, shell);
	if (cmds)
		free_commands(cmds, num_commands);
	return (status);
}

int	handle_single_command_execution(char **tokens,
	t_shell *shell, t_plchild_data *d)
{
	t_command	*cmd;
	int			status;
	int			i;

	cmd = parse_command(tokens, shell->last_exit_status, shell);
	if (!cmd)
	{
		i = 0;
		while (tokens[i])
			free(tokens[i++]);
		free(tokens);
		if (errno == ENOENT)
			shell->last_exit_status = 1;
		else
			shell->last_exit_status = 2;
		return (shell->last_exit_status);
	}
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
	status = execute_command(cmd, shell, d);
	free_command(cmd);
	return (status);
}

int	process_line(char **tokens, t_shell *shell, t_plchild_data *d)
{
	int	status;

	if (handle_empty_tokens(tokens))
		return (0);
	if (!tokens[0])
		return (0);
	if (handle_syntax_and_redir_errors(tokens, shell) != 0)
		return (shell->last_exit_status);
	if (ft_strcmp(tokens[0], "exit") == 0 && count_pipes(tokens) == 0)
	{
		rl_clear_history();
		return (builtin_exit(tokens, d, shell));
	}
	if (count_pipes(tokens) > 0)
	{
		status = handle_pipeline_execution(tokens, shell);
	}
	else
		status = handle_single_command_execution(tokens, shell, d);
	shell->last_exit_status = status;
	return (status);
}

void	process_tokens(char **tokens, t_shell *shell, t_plchild_data *d)
{
	int	i;

	if (!tokens || !tokens[0])
	{
		if (tokens)
			free(tokens);
		return ;
	}
	shell->last_exit_status = process_line(tokens, shell, d);
	if (d && d->cmds)
	{
		i = 0;
		while (d->cmds[i])
			free_command(d->cmds[i++]);
		free(d->cmds);
		exit(1);
	}
	if (shell->last_exit_status == 2 && !isatty(STDIN_FILENO))
		exit(shell->last_exit_status);
}

void	process_input_line(char *line, t_shell *shell, t_plchild_data *d)
{
	char	**tokens;

	if (!*line)
	{
		free(line);
		return ;
	}
	add_history(line);
	tokens = parse_input(line, shell->last_exit_status, shell);
	free(line);
	process_tokens(tokens, shell, d);
}
