/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:13:21 by bgroz             #+#    #+#             */
/*   Updated: 2024/04/18 14:21:43 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	char		ch;
	const char	*str;

	ch = c;
	i = 0;
	str = (const char *) s;
	while (i < n)
	{
		if (str[i] == ch)
		{
			return ((char *)&str[i]);
		}
		i++;
	}
	if (i == n)
		return (NULL);
	return (0);
}
