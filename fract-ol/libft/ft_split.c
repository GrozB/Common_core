/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:32:27 by bgroz             #+#    #+#             */
/*   Updated: 2024/04/19 14:45:06 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static int	ft_strcount(const char *str, char c)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] != c && flag == 0)
		{
			flag = 1;
			j++;
		}
		else if (str[i] == c)
			flag = 0;
		i++;
	}
	return (j);
}

static void	ft_free(char **arr, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	ft_split_substr(char const *s, char c, char **res)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		k = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (i > k)
		{
			res[j] = ft_substr(s, k, i - k);
			if (res[j] == NULL)
				return (j);
			j++;
		}
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	store;
	size_t	substr;

	if (s == NULL)
		return (NULL);
	store = ft_strcount(s, c);
	res = (char **)malloc((store + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	substr = ft_split_substr(s, c, res);
	if (substr < store)
	{
		ft_free(res, substr);
		return (NULL);
	}
	res[substr] = NULL;
	return (res);
}
