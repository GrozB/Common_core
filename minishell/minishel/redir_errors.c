/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <amadiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:32:56 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/13 16:38:51 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

int	check_redir_pair(char *current, char *next)
{
	if ((ft_strcmp(current, ">") == 0 || ft_strcmp(current, ">>") == 0)
		&& (ft_strcmp(next, ">") == 0 || ft_strcmp(next, ">>") == 0))
	{
		write(STDERR_FILENO,
			"minishell: syntax error near unexpected token `>'\n", 50);
		return (2);
	}
	if ((ft_strcmp(current, "<") == 0 || ft_strcmp(current, "<<") == 0)
		&& (ft_strcmp(next, "<") == 0 || ft_strcmp(next, "<<") == 0))
	{
		write(STDERR_FILENO,
			"minishell: syntax error near unexpected token `<'\n", 50);
		return (2);
	}
	return (0);
}

int	check_consecutive_redirs(char **tokens)
{
	int	i;
	int	error_code;

	i = 0;
	if (!tokens || !tokens[0])
		return (0);
	while (tokens[i])
	{
		if (tokens[i + 1])
		{
			error_code = check_redir_pair(tokens[i], tokens[i + 1]);
			if (error_code != 0)
				return (error_code);
		}
		i++;
	}
	return (0);
}

int	handle_empty_tokens(char **tokens)
{
	int	i;

	if (tokens && tokens[0])
	{
		if (!(ft_strcmp(tokens[0], "export") == 0
				|| ft_strcmp(tokens[0], "unset") == 0))
		{
			return (0);
		}
	}
	if (!tokens || !tokens[0])
	{
		if (tokens)
		{
			i = 0;
			while (tokens[i])
				free(tokens[i++]);
			free(tokens);
		}
		return (1);
	}
	return (0);
}

int	handle_syntax_errors(char **tokens, t_shell *shell)
{
	int	i;
	int	syntax_error_code;

	syntax_error_code = check_syntax_errors(tokens);
	if (syntax_error_code != 0)
	{
		shell->last_exit_status = syntax_error_code;
		i = 0;
		while (tokens[i])
			free(tokens[i++]);
		free(tokens);
		return (syntax_error_code);
	}
	return (0);
}

int	handle_redirection_errors(char **tokens, t_shell *shell)
{
	int	i;
	int	redir_err;

	redir_err = check_consecutive_redirs(tokens);
	if (redir_err != 0)
	{
		shell->last_exit_status = redir_err;
		i = 0;
		while (tokens[i])
			free(tokens[i++]);
		free(tokens);
		return (redir_err);
	}
	return (0);
}
