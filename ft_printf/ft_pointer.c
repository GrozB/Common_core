/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:55:02 by bgroz             #+#    #+#             */
/*   Updated: 2024/04/30 12:11:49 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pointer(void *value)
{
	int			count;
	long long	ptr;

	ptr = (long long)value;
	count = 0;
	if (ptr == 0)
	{
		count += write(1, "(nil)", 5);
		return (count);
	}
	else
	{
		count += write(1, "0x", 2);
		count += ft_hexadec_long(ptr);
	}
	return (count);
}
