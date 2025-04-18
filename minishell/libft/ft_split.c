/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 10:18:29 by amadiev           #+#    #+#             */
/*   Updated: 2024/04/14 12:12:42 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	counter(char const *s, char c)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static size_t	wordlen(const char *s, char c)
{
	if (!ft_strchr(s, c))
		return (ft_strlen(s));
	return (ft_strchr(s, c) - s);
}

static void	*clean(char **str, int i)
{
	while (i-- > 0)
		free(str[i]);
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	word_len;
	int		i;

	if (!s)
		return (NULL);
	arr = (char **)malloc((counter(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (!*s)
			break ;
		word_len = wordlen(s, c);
		arr[i] = ft_substr(s, 0, word_len);
		if (!arr[i++])
			return (clean(arr, --i));
		s += word_len;
	}
	arr[i] = NULL;
	return (arr);
}
