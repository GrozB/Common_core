/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <amadiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:44:17 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/13 14:29:56 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_expansion.h"

int	check_pipe_and_redir_syntax(char **tokens, int i)
{
	int	ret;

	if (ft_strcmp(tokens[i], "|") == 0)
	{
		if (!tokens[i + 1])
		{
			write(2, "minishell: syntax error near unexpected token `|'\n", 50);
			return (2);
		}
	}
	else if (ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0
		|| ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], "<<") == 0)
	{
		ret = check_redirection_syntax(tokens, i);
		if (ret != 0)
			return (ret);
	}
	return (0);
}

int	check_syntax_errors(char **tokens)
{
	int	i;
	int	ret;

	ret = check_pipe_syntax(tokens);
	if (ret != 0)
		return (ret);
	i = 0;
	while (tokens[i])
	{
		ret = check_pipe_and_redir_syntax(tokens, i);
		if (ret != 0)
			return (ret);
		i++;
	}
	return (check_trailing_pipe_or_redir(tokens, i));
}
