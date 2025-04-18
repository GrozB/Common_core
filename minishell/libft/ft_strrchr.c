/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:09:38 by amadiev           #+#    #+#             */
/*   Updated: 2024/04/13 12:32:06 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last_occurance;

	last_occurance = NULL;
	while (*s)
	{
		if (*s == (char)c)
			last_occurance = s;
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return ((char *)last_occurance);
}
