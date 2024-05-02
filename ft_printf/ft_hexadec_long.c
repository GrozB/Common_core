/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexadec_long.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:58:12 by bgroz             #+#    #+#             */
/*   Updated: 2024/04/30 12:53:52 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_zero(char *str)
{
	write(1, "0", 1);
	free (str);
	return (1);
}

static int	all_in_one(char *str)
{
	int	len;

	if (str == NULL)
		return (0);
	len = ft_strlen(str);
	write(1, str, len);
	free(str);
	return (len);
}

static int	ft_calculation_positive(long long value, char *str)
{
	unsigned int	dig;
	int				i;

	i = 0;
	while (value > 0)
	{
		dig = value % 16;
		if (dig < 10)
			str[i++] = dig + '0';
		else
			str[i++] = dig - 10 + 'a';
		value /= 16;
	}
	str[i] = '\0';
	ft_strrev(str);
	return (1);
}

static int	ft_calculation_negative(long long value, char *str)
{
	unsigned int		dig;
	int					i;
	unsigned long long	uvalue;

	i = 0;
	uvalue = (unsigned long long)value;
	while (uvalue > 0)
	{
		dig = uvalue % 16;
		if (dig < 10)
			str[i++] = dig + '0';
		else
			str[i++] = dig - 10 + 'a';
		uvalue /= 16;
	}
	str[i] = '\0';
	ft_strrev(str);
	return (1);
}

int	ft_hexadec_long(long long value)
{
	char			*str;

	str = (char *)malloc(33);
	if (str == NULL)
		return (0);
	ft_memset (str, 0, 33);
	if (value == 0)
		return (ft_zero(str));
	else if (value > 0)
		ft_calculation_positive(value, str);
	else
		ft_calculation_negative(value, str);
	return (all_in_one(str));
}
