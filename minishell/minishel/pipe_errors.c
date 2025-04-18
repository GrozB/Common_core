/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <amadiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:32:56 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/13 16:39:27 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

int	handle_pipe_redirection_errors(char **tokens, t_shell *shell)
{
	int	i;

	i = -1;
	while (tokens[++i])
	{
		if ((ft_strcmp(tokens[i], ">>") == 0 || ft_strcmp(tokens[i], ">") == 0
				|| ft_strcmp(tokens[i], "<<") == 0
				|| ft_strcmp(tokens[i], "<") == 0)
			&& tokens[i + 1] && ft_strcmp(tokens[i + 1], "|") == 0)
		{
			write(STDERR_FILENO,
				"minishell: syntax error near unexpected token '|'\n", 51);
			shell->last_exit_status = 2;
			i = 0;
			while (tokens[i])
				free(tokens[i++]);
			free(tokens);
			return (2);
		}
	}
	return (0);
}

int	handle_syntax_and_redir_errors(char **tokens, t_shell *shell)
{
	if (handle_syntax_errors(tokens, shell) != 0)
		return (shell->last_exit_status);
	if (handle_redirection_errors(tokens, shell) != 0)
		return (shell->last_exit_status);
	if (handle_pipe_redirection_errors(tokens, shell) != 0)
		return (shell->last_exit_status);
	return (0);
}
