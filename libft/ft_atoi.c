/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:35:06 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/07 19:05:42 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int	ft_overflow(long res, int dig, int sign)
{
	if (sign == 1)
	{
		if (res > (LONG_MAX - dig) / 10)
			return (INT_MAX);
	}
	else
	{
		if (-res < (LONG_MIN + dig) / 10)
			return (INT_MIN);
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	long	res;
	int		sign;
	int		overflow;

	sign = 1;
	res = 0;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		overflow = ft_overflow(res, nptr[i] - '0', sign);
		if (overflow != 1)
			return (overflow);
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
}
