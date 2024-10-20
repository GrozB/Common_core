/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_dec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:00:14 by bgroz             #+#    #+#             */
/*   Updated: 2024/07/04 10:57:33 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
		count += ft_putchar(n + '0');
	return (count);
}
