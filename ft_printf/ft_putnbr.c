/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:32:27 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/07 17:47:29 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbrr(int n)
{
	int	count;

	count = 0;
	if (n == INT_MIN)
	{
		count = write(1, "-2147483648", 11);
		return (count);
	}
	else
	{
		if (n < 0)
		{
			count += write(1, "-", 1);
			n = n * -1;
		}
		if (n > 9)
		{
			count += ft_putnbrr(n / 10);
			count += ft_putnbrr(n % 10);
		}
		else
			count += ft_putcharr(n + '0');
	}
	return (count);
}
