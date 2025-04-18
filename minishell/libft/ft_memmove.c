/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:34:48 by amadiev           #+#    #+#             */
/*   Updated: 2024/04/20 12:23:46 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*cdest;
	const char	*csrc;
	size_t		i;

	i = 0;
	cdest = dest;
	csrc = src;
	if (!cdest && !csrc)
		return (NULL);
	if (csrc < cdest)
		while (++i <= n)
			cdest[n - i] = csrc[n - i];
	else
		while (n-- > 0)
			*(cdest++) = *(csrc++);
	return (dest);
}
