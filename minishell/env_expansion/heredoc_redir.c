/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:44:01 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/14 20:13:41 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_expansion.h"

int	handle_heredoc_redir(t_command *cmd,
	char *filename, int last_exit_status, t_shell *shell)
{
	int	fd;
	int	result;

	fd = handle_here_doc(filename, last_exit_status, shell);
	if (fd < 0)
	{
		if (!g_parent_interrupted)
			free(filename);
		return (-1);
	}
	result = add_redir(cmd, REDIR_HEREDOC, filename);
	if (!result)
		return (-1);
	cmd->redirs[cmd->nb_redirs - 1].here_doc_fd = fd;
	return (0);
}

static int	handle_tventy_five_lines(void)
{
	write(2,
		"minishell: syntax error near unexpected token 'newline'\n", 56);
	return (-1);
}

int	handle_redirection(t_command *cmd,
					char ***tokens, int last_exit_status, t_shell *shell)
{
	char	*op;
	char	*filename;
	char	*redir[2];

	op = **tokens;
	(*tokens)++;
	if (!**tokens)
		return (handle_tventy_five_lines());
	filename = get_filename(op, **tokens);
	if (!filename)
		return (-1);
	redir[0] = op;
	redir[1] = filename;
	shell->last_exit_status = last_exit_status;
	if (handle_redir_type(cmd, redir, shell) < 0)
	{
		free(filename);
		return (-1);
	}
	free(filename);
	(*tokens)++;
	return (0);
}

int	handle_redir_type(t_command *cmd, char **redir, t_shell *shell)
{
	int	result;

	result = 0;
	if (ft_strcmp(redir[0], ">") == 0)
		result = add_redir(cmd, REDIR_OUT, redir[1]);
	else if (ft_strcmp(redir[0], ">>") == 0)
		result = add_redir(cmd, REDIR_OUT_APPEND, redir[1]);
	else if (ft_strcmp(redir[0], "<") == 0)
		result = add_redir(cmd, REDIR_IN, redir[1]);
	else if (ft_strcmp(redir[0], "<<") == 0)
	{
		if (handle_heredoc_redir(cmd,
				redir[1], shell->last_exit_status, shell) < 0)
			return (-1);
		return (0);
	}
	if (result)
		return (0);
	return (-1);
}
