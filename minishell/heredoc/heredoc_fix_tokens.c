/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_fix_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:28:53 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 17:44:12 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static int	count_new_tokens(char **tokens)
{
	int	i;
	int	new_count;

	i = 0;
	new_count = 0;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "<<", 2) == 0 && tokens[i][2] != '\0')
			new_count += 2;
		else
			new_count += 1;
		i++;
	}
	return (new_count);
}

static char	**allocate_new_tokens(int new_count)
{
	int		i;
	char	**new_tokens;

	new_tokens = malloc(sizeof(char *) * (new_count + 1));
	if (!new_tokens)
		return (NULL);
	i = 0;
	while (i < new_count + 1)
	{
		new_tokens[i] = NULL;
		i++;
	}
	return (new_tokens);
}

static int	handle_split_token(char **tokens, char **new_tokens, int *i, int *j)
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

static int	process_tokens(char **tokens, char **new_tokens, int *actual_count)
{
	int	i;
	int	j;
	int	success;

	i = 0;
	j = 0;
	success = 1;
	while (success && tokens[i])
	{
		if (ft_strncmp(tokens[i], "<<", 2) == 0 && tokens[i][2] != '\0')
			success = handle_split_token(tokens, new_tokens, &i, &j);
		else
		{
			new_tokens[j] = tokens[i];
			j++;
		}
		i++;
	}
	if (success)
		new_tokens[j] = NULL;
	*actual_count = j;
	return (success);
}

char	**fix_here_doc_tokens(char **tokens)
{
	char	**new_tokens;
	int		new_count;
	int		actual_count;
	int		success;

	if (!tokens)
		return (NULL);
	new_count = count_new_tokens(tokens);
	new_tokens = allocate_new_tokens(new_count);
	if (!new_tokens)
		return (NULL);
	success = process_tokens(tokens, new_tokens, &actual_count);
	if (!success)
	{
		free_new_tokens_on_failure(new_tokens, actual_count);
		return (NULL);
	}
	return (new_tokens);
}
