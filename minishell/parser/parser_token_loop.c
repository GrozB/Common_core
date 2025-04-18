/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_loop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:04:42 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 18:15:55 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	process_token(char **tokens, char **new_tokens, int *i, int *j)
{
	int	success;

	success = 1;
	if (tokens[*i][0] == '\x01')
	{
		new_tokens[*j] = tokens[*i];
		tokens[*i] = NULL;
		(*j)++;
	}
	else if (tokens[*i][0] == '<'
				&& tokens[*i][1] == '<' && tokens[*i][2] != '\0')
		success = handle_heredoc_token(tokens, new_tokens, i, j);
	else
		success = handle_split_token(tokens, new_tokens, i, j);
	return (success);
}

int	process_tokens_loop(char **tokens, char **new_tokens, int *success)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*success && tokens[i])
	{
		*success = process_token(tokens, new_tokens, &i, &j);
		i++;
	}
	if (*success)
		new_tokens[j] = NULL;
	return (j);
}

int	fill_new_tokens(char **tokens, char **new_tokens, int new_count)
{
	int	success;
	int	j;

	(void)new_count;
	success = 1;
	j = process_tokens_loop(tokens, new_tokens, &success);
	if (!success)
	{
		while (--j >= 0)
		{
			if (new_tokens[j] != g_empty_str())
				free(new_tokens[j]);
		}
		free(new_tokens);
		new_tokens = NULL;
	}
	return (success);
}

void	free_split_and_tokens(char **split, char **tokens, int *i)
{
	free(split[0]);
	if (split[1])
		free(split[1]);
	free(split);
	free(tokens[*i]);
	tokens[*i] = NULL;
}

void	free_str_array_partial(char **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
