/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 10:24:07 by amadiev           #+#    #+#             */
/*   Updated: 2024/04/20 12:07:35 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long int	a;

	a = n;
	if (a < 0)
	{
		ft_putchar_fd('-', fd);
		a *= -1 ;
	}
	if (a > 9)
		ft_putnbr_fd(a / 10, fd);
	ft_putchar_fd(a % 10 + 48, fd);
}
