/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:43:20 by bgroz             #+#    #+#             */
/*   Updated: 2024/09/18 19:48:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
//#include <bsd/string.h>
#include <string.h>
#include "libft.h"

static int ft_strlenn(const char *str)
{
	int	i;

	i = 0;
	while(str)
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	if (dst == NULL && size == 0 && src != 0)
		return (0);
	j = 0;
	dst_len = ft_strlenn(dst);
	src_len = ft_strlenn(src);
	i = dst_len;
	if (size <= dst_len)
		return (size + src_len);
	while (src[j] != '\0' && i < size - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst_len + src_len);
}
