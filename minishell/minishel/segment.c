/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <amadiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:32:56 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/13 16:36:33 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

char	**build_segment(char **tokens, int start, int len)
{
	int		j;
	char	**seg;

	j = 0;
	if (!tokens)
		return (NULL);
	seg = malloc(sizeof(char *) * (len + 1));
	if (!seg)
		return (NULL);
	while (j < len)
	{
		seg[j] = ft_strdup(tokens[start + j]);
		if (!seg[j])
		{
			while (j > 0)
				free(seg[--j]);
			free(seg);
			return (NULL);
		}
		j++;
	}
	seg[len] = NULL;
	return (seg);
}

void	free_segment(char **seg)
{
	int	j;

	j = 0;
	while (seg[j])
	{
		free(seg[j]);
		j++;
	}
	free(seg);
}

int	next_pipe(char **tokens, int start)
{
	int	i;

	i = start;
	if (!tokens)
		return (-1);
	while (tokens[i] && !(tokens[i][0] == '|' && tokens[i][1] == '\0'))
		i++;
	return (i);
}

int	validate_split_conditions(char **tokens, int *num_commands)
{
	if (!tokens || !num_commands
		|| check_pipe_token(tokens) < 0
		|| check_trailing_pipe(tokens) < 0)
	{
		return (-1);
	}
	return (0);
}
