/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <amadiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:44:33 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/13 14:30:22 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_expansion.h"

int	count_words(const char *str)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (str[i])
	{
		if (ft_isspace((unsigned char)str[i]))
			in_word = 0;
		else if (!in_word)
		{
			count++;
			in_word = 1;
		}
		i++;
	}
	return (count);
}

char	*allocate_word(const char *str, int start, int len)
{
	char	*word;

	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strncpy(word, str + start, len);
	word[len] = '\0';
	return (word);
}

char	**free_words(char **words, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(words[i]);
		i++;
	}
	free(words);
	return (NULL);
}

char	**split_words(const char *str, int word_count)
{
	char	**words;
	int		i;
	int		index;
	int		start;

	words = malloc(sizeof(char *) * (word_count + 1));
	if (!words)
		return (NULL);
	i = 0;
	index = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace((unsigned char)str[i]))
			i++;
		if (!str[i])
			break ;
		start = i;
		while (str[i] && !ft_isspace((unsigned char)str[i]))
			i++;
		words[index] = allocate_word(str, start, i - start);
		if (!words[index++])
			return (free_words(words, index - 1));
	}
	words[index] = NULL;
	return (words);
}

char	**word_split(const char *str)
{
	int	word_count;

	if (!str)
		return (NULL);
	word_count = count_words(str);
	return (split_words(str, word_count));
}
