/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:47:25 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/11 10:34:40 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
	{
		i++;
	}
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	size;
	char	*result;
	int		i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (size == 0)
		return (NULL);
	result = (char *)malloc(size);
	if (result == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	ft_strcat(result, s2);
	return (result);
}

char	*ft_strdup(const char *s)
{
	int		len;
	char	*dup;
	int		i;

	len = 0;
	i = 0;
	if (!s)
		return (NULL);
	while (s[len])
	{
		len++;
	}
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (dup == 0)
		return (0);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	ch;

	ch = c;
	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != ch)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	if (s[i] == ch)
	{
		return ((char *)&s[i]);
	}
	return (0);
}
