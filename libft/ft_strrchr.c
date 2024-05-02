/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:47:33 by bgroz             #+#    #+#             */
/*   Updated: 2024/04/16 16:36:30 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	ch;

	ch = c;
	i = ft_strlen(s);
	if (ch == '\0')
		return ((char *)&s[i]);
	i--;
	while (i >= 0)
	{
		if (s[i] == ch)
		{
			return ((char *)&s[i]);
		}
		i--;
	}
	return (0);
}
