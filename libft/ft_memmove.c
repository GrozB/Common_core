/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:27:28 by bgroz             #+#    #+#             */
/*   Updated: 2024/04/19 16:23:57 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*c_dest;
	const char	*c_src;

	c_dest = (char *) dest;
	c_src = (const char *) src;
	if (c_dest == NULL && c_src == NULL && n > 0)
		return (NULL);
	if (c_dest > c_src)
	{
		while (n--)
		{
			c_dest[n] = c_src[n];
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			c_dest[i] = c_src[i];
			i++;
		}
	}
	return (c_dest);
}

int	main(void)
{
	char	dst[] = "Where to copy";
	const char	src[] = "this";
	size_t	n = -1;

	printf ("My Result is:%s\n", (char *)ft_memmove(dst, src, n));
	printf ("Original Result is:%s\n", (char *)memmove(dst, src, n));
}