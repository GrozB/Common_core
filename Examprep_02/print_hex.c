/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 10:52:07 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/28 12:36:00 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_atoi(char *nptr)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	while (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
}

void ft_putnbr(int n)
{
	char	c;
	int		store;
	
	store = n % 16;
	if (n > 15)
	{
		ft_putnbr(n / 16);
	}
	
	if (store < 10)
	{
		c = store + '0';
		write(1, &c, 1);
	}
	else
	{
		c = store - 10 + 'a';
		write(1, &c, 1);
	}
}

int	main(int argc, char **argv)
{
	int	number;
	
	if (argc == 2)
	{
		number = ft_atoi(argv[1]);
		ft_putnbr(number);
	}
	write(1, "\n", 1);
	return (0);
}