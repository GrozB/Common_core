/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:32:27 by bgroz             #+#    #+#             */
/*   Updated: 2024/07/04 10:58:19 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n)
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
			count += ft_putnbr(n / 10);
			count += ft_putnbr(n % 10);
		}
		else
			count += ft_putchar(n + '0');
	}
	return (count);
}
