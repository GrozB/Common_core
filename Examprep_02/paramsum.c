/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paramsum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:44:01 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/27 10:03:14 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr(int n)
{
	char	digit;
	
	if (n >= 10)
	{
		ft_putnbr(n / 10);
	}
	digit = n % 10 + '0';
	write(1, &digit, 1);
}

int	main(int argc, char **argv)
{
	int	j;

	j = 1;
	if (!argc)
	{
		write(1, "0\n", 2);
		return (0);
	}
	while (argc > j)
	{
		j++;
	}
	if (argc == j)
	{
		ft_putnbr(j - 1);
	}
	write(1, "\n", 1);
	return (0);
}