/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_rest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:51:37 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 17:19:11 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static long long	ft_atoll_core(const char *str, char **endptr, int sign)
{
	long long	result;

	result = 0;
	while (*str && ft_isdigit((unsigned char)*str))
	{
		if ((sign == 1 && (result > (LLONG_MAX - (*str - '0')) / 10))
			|| (sign == -1 && (-result < (LLONG_MIN + (*str - '0')) / 10)))
		{
			errno = ERANGE;
			while (ft_isdigit((unsigned char)*str))
				str++;
			break ;
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	if (endptr)
		*endptr = (char *)str;
	return (result * sign);
}

long long	ft_atoll(const char *str, char **endptr)
{
	int	sign;

	sign = 1;
	while (*str && ft_isspace((unsigned char)*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	return (ft_atoll_core(str, endptr, sign));
}
