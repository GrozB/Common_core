/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:27:27 by bgroz             #+#    #+#             */
/*   Updated: 2024/04/16 16:36:47 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static int	ft_inset(char c, char const *s1)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	str_len;
	size_t	str_beg;
	size_t	str_end;
	char	*res;

	str_beg = 0;
	if (s1 == 0 || set == 0)
		return (NULL);
	str_len = ft_strlen(s1);
	if (str_len == 0)
		return (ft_strdup(""));
	str_end = str_len - 1;
	while (ft_inset(s1[str_beg], set) && str_beg < str_len)
		str_beg++;
	if (str_beg == str_len)
		return (ft_strdup(""));
	while (ft_inset(s1[str_end], set) && str_end > str_beg)
		str_end--;
	res = ft_substr(s1, str_beg, (str_end - str_beg) + 1);
	return (res);
}
