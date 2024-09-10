/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:00:30 by bgroz             #+#    #+#             */
/*   Updated: 2024/07/04 11:02:07 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "libft.h"

static char	*ft_strrevcomp(char *str, int neg)
{
	int		i;
	int		index;
	char	c;

	index = 0;
	i = neg;
	while (str[index] != '\0')
	{
		index++;
	}
	index--;
	while (i < (index))
	{
		c = str[i];
		str[i] = str[index];
		str[index] = c;
		i++;
		index--;
	}
	return (str);
}

static int	ft_num_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static void	ft_fill(char *res, unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
	{
		res[0] = '0';
		i++;
	}
	while (n != 0)
	{
		res[i] = (n % 10) + '0';
		n = n / 10;
		i++;
	}
	res[i] = '\0';
}

char	*ft_itoa(int n)
{
	char			*res;
	int				sign;
	unsigned int	un;
	int				extra;

	sign = 1;
	extra = 0;
	if (n < 0)
		sign = -1;
	if (n == INT_MIN)
		un = (unsigned int)INT_MAX + 1;
	else if (sign == -1)
		un = -n;
	else
		un = n;
	if (sign == -1)
		extra = 1;
	res = malloc(ft_num_len(un) + 1 + extra);
	if (res == NULL)
		return (NULL);
	ft_fill(res + extra, un);
	if (sign == -1)
		res[0] = '-';
	return (ft_strrevcomp(res, extra));
}
