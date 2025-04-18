/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <amadiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:32:56 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/13 16:52:56 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

int	count_pipes(char **tokens)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '|' && tokens[i][1] == '\0')
			count++;
		i++;
	}
	return (count);
}

int	check_trailing_pipe(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return (-1);
	while (tokens[i])
		i++;
	if (i > 0 && tokens[i - 1] && ft_strcmp(tokens[i - 1], "|") == 0)
	{
		write(STDERR_FILENO,
			"minishell: syntax error near unexpected token '|'\n", 51);
		return (-1);
	}
	if (i > 0 && tokens[i - 1][0] == '|' && tokens[i - 1][1] == '\0')
	{
		write(STDERR_FILENO, "minishell: syntax error: empty command\n", 39);
		return (-1);
	}
	return (0);
}

int	validate_pipe_token(char *token)
{
	if (token[0] == '\x01')
		return (0);
	if (ft_strchr(token, '|'))
	{
		if (ft_strcmp(token, "|") != 0)
		{
			write(STDERR_FILENO,
				"minishell: syntax error near unexpected token '",
				46);
			write(STDERR_FILENO, token + 1, ft_strlen(token + 1));
			write(STDERR_FILENO, "'\n", 2);
			return (-1);
		}
		if (token[0] != '|' || token[1] != '\0')
		{
			write(STDERR_FILENO,
				"minishell: syntax error: invalid pipe token\n",
				43);
			return (-1);
		}
	}
	return (0);
}

int	check_pipe_token(char **tokens)
{
	int	i;

	if (!tokens)
		return (-1);
	i = 0;
	while (tokens[i])
	{
		if (validate_pipe_token(tokens[i]) < 0)
			return (-1);
		i++;
	}
	return (0);
}

int	remove_empty_tokens(char **tokens)
{
	int	k;

	while (tokens && tokens[0] && tokens[0][0] == '\0')
	{
		free(tokens[0]);
		k = 0;
		while (tokens[k + 1])
		{
			tokens[k] = tokens[k + 1];
			k++;
		}
		tokens[k] = NULL;
	}
	return (0);
}
