/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <amadiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:43:58 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/13 14:28:57 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_expansion.h"

char	*get_filename_from_words(char *token)
{
	char	**words;
	char	*filename;

	words = word_split(token);
	if (!words || !words[0] || words[0][0] == '\0')
	{
		write(2, "minishell: ", 11);
		write(2, token, ft_strlen(token));
		write(2, ": ambiguous redirect\n", 21);
		free_str_array(words);
		return (NULL);
	}
	if (words[1] != NULL)
	{
		write(2, "minishell: ", 11);
		write(2, token, ft_strlen(token));
		write(2, ": ambiguous redirect\n", 21);
		free_str_array(words);
		return (NULL);
	}
	filename = ft_strdup(words[0]);
	free_str_array(words);
	return (filename);
}

char	*get_filename(char *op, char *token)
{
	char	*filename;

	filename = NULL;
	if (ft_strcmp(op, "<<") == 0)
		filename = ft_strdup(token);
	else
	{
		if (token[0] == '\x01')
			filename = ft_strdup(token + 1);
		else
			filename = get_filename_from_words(token);
	}
	return (filename);
}
