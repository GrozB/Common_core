/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:03:48 by amadiev           #+#    #+#             */
/*   Updated: 2024/04/14 11:07:01 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*cdest;
	const char	*csrc;

	if (!dest && !src)
		return (NULL);
	cdest = dest;
	csrc = src;
	while (n--)
		*cdest++ = *csrc++;
	return (dest);
}
