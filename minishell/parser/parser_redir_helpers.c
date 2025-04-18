/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:03:06 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 18:13:39 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	count_split_tokens(char **tokens, int *new_count, int i)
{
	char	**split;

	split = split_redir_token(tokens[i]);
	if (!split)
	{
		(*new_count)++;
	}
	else
	{
		if (split[1] != NULL)
			(*new_count) += 2;
		else
			(*new_count) += 1;
		free(split[0]);
		if (split[1])
			free(split[1]);
		free(split);
	}
	return (0);
}

int	handle_split_token(char **tokens, char **new_tokens, int *i, int *j)
{
	char	**split;

	split = split_redir_token(tokens[*i]);
	if (!split)
	{
		new_tokens[*j] = tokens[*i];
		(*j)++;
		tokens[*i] = NULL;
		return (1);
	}
	if (!copy_split_to_new_tokens(new_tokens, j, split))
	{
		free_split_and_tokens(split, tokens, i);
		return (0);
	}
	free_split_and_tokens(split, tokens, i);
	return (1);
}

int	handle_heredoc_token(char **tokens,
	char **new_tokens, int *i, int *j)
{
	new_tokens[*j] = ft_strdup("<<");
	if (!new_tokens[*j])
		return (0);
	(*j)++;
	new_tokens[*j] = ft_strdup(tokens[*i] + 2);
	if (!new_tokens[*j])
		return (0);
	(*j)++;
	free(tokens[*i]);
	tokens[*i] = NULL;
	return (1);
}

static int	copy_split_part(char **new_tokens, int *j, char *split_part)
{
	char	*token;

	token = ft_strdup(split_part);
	if (!token)
		return (0);
	if (ft_strcmp(token, "") == 0)
	{
		free(token);
		token = ft_strdup("");
		if (!token)
			return (0);
	}
	new_tokens[*j] = token;
	(*j)++;
	return (1);
}

int	copy_split_to_new_tokens(char **new_tokens, int *j, char **split)
{
	if (!copy_split_part(new_tokens, j, split[0]))
		return (0);
	if (split[1])
	{
		if (!copy_split_part(new_tokens, j, split[1]))
		{
			if (new_tokens[*j - 1])
				free(new_tokens[*j - 1]);
			new_tokens[*j - 1] = NULL;
			return (0);
		}
	}
	return (1);
}
