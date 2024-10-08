/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_dec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:00:14 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/07 17:47:36 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_unsigned_dec(unsigned int n)
{
	int	count;

	count = 0;
	if (n > 9)
	{
		count += ft_unsigned_dec(n / 10);
		count += ft_unsigned_dec(n % 10);
	}
	else
		count += ft_putcharr(n + '0');
	return (count);
}
