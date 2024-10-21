/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:18:42 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/07 17:47:30 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstrr(char *s)
{
	int	i;
	int	count;

	count = 0;
	if (!s)
		return (write(1, "(null)", 6));
	i = 0;
	while (s[i])
	{
		count += ft_putcharr((int)s[i]);
		i++;
	}
	return (count);
}
