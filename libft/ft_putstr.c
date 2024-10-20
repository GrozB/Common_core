/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:18:42 by bgroz             #+#    #+#             */
/*   Updated: 2024/07/04 10:58:11 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *s)
{
	int	i;
	int	count;

	count = 0;
	if (!s)
		return (write(1, "(null)", 6));
	i = 0;
	while (s[i])
	{
		count += ft_putchar((int)s[i]);
		i++;
	}
	return (count);
}
