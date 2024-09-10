/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:50:53 by bgroz             #+#    #+#             */
/*   Updated: 2024/04/16 15:53:30 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static size_t	adj_len(char const *s, unsigned int start, size_t len)
{
	size_t	str_len;

	str_len = ft_strlen(s);
	if (str_len <= start)
		return (0);
	if (len > str_len - start)
		len = str_len - start;
	return (len);
}

static char	*len_zero(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	len = adj_len(s, start, len);
	if (len == 0)
	{
		substr = (char *)malloc(1);
		if (substr == 0)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*substr;

	i = 0;
	j = 0;
	if (s == 0)
		return (NULL);
	len = adj_len(s, start, len);
	if (len == 0)
		return (len_zero(s, start, len));
	substr = (char *)malloc(len + 1);
	if (substr == 0)
		return (NULL);
	while (s[i] != '\0' && i < start)
		i++;
	while (s[i] != '\0' && j < len)
	{
		substr[j] = s[i];
		i++;
		j++;
	}
	substr[j] = '\0';
	return (substr);
}
