/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <amadiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:44:14 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/13 14:29:52 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_expansion.h"

int	check_pipe_syntax(char **tokens)
{
	if (!tokens || !tokens[0])
		return (0);
	if (ft_strcmp(tokens[0], "|") == 0)
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
		return (2);
	}
	return (0);
}

int	check_unexpected_newline(char **tokens, int i)
{
	if (!tokens[i + 1])
	{
		write(2,
			"minishell: syntax error near unexpected token `newline'\n", 56);
		return (2);
	}
	return (0);
}

int	check_redirection_syntax_error(char **tokens, int i)
{
	char	*err_token;
	int		ret;

	ret = check_unexpected_newline(tokens, i);
	if (ret != 0)
		return (ret);
	if (ft_strcmp(tokens[i + 1], "|") == 0 || is_redirection(tokens[i + 1]))
	{
		if ((ft_strcmp(tokens[i], ">") == 0
				&& ft_strcmp(tokens[i + 1], ">>") == 0)
			|| (ft_strcmp(tokens[i], ">>") == 0
				&& ft_strcmp(tokens[i + 1], ">") == 0)
			|| (ft_strcmp(tokens[i], "<") == 0
				&& ft_strcmp(tokens[i + 1], "<<") == 0)
			|| (ft_strcmp(tokens[i], "<<") == 0
				&& ft_strcmp(tokens[i + 1], "<") == 0))
			err_token = tokens[i];
		else
			err_token = tokens[i + 1];
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, err_token, ft_strlen(err_token));
		write(2, "'\n", 2);
		return (2);
	}
	return (0);
}

int	check_redirection_syntax(char **tokens, int i)
{
	if (check_redirection_syntax_error(tokens, i) != 0)
		return (2);
	if (i != 0 && ft_strcmp(tokens[i - 1], "|") != 0)
		return (0);
	return (0);
}

int	check_trailing_pipe_or_redir(char **tokens, int i)
{
	if (i > 0 && (ft_strcmp(tokens[i - 1], "|") == 0
			|| is_redirection(tokens[i - 1])))
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
		return (2);
	}
	return (0);
}
