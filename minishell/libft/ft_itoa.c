/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 10:20:49 by amadiev           #+#    #+#             */
/*   Updated: 2024/04/15 17:09:15 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(int num)
{
	int	count;

	count = 0;
	while (num != 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}

static char	*zero(char *str)
{
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*str;
	int		znak;

	count = len(n);
	znak = 1;
	if (n < 0)
		znak = -1;
	count = count + (n <= 0);
	str = (char *)malloc(sizeof(char) * (count + 1));
	if (!str)
		return (NULL);
	if (n == 0)
		return (zero(str));
	str[count] = '\0';
	while (n != 0)
	{
		str[--count] = (char)((n % 10) * znak + '0');
		n = n / 10;
	}
	count--;
	if (znak < 0)
		str[count] = '-';
	return (str);
}
