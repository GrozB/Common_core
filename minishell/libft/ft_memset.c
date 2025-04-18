/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:08:39 by amadiev           #+#    #+#             */
/*   Updated: 2024/04/14 12:31:16 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*filling the memory with a constant byte*/
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;

	str = s;
	while (n--)
		*str++ = (unsigned char)c;
	return (s);
}
