/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_prime_sum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:49:43 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/23 09:17:23 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	is_prime(int n)
{
	int	i;

	i = 2;
	if (n <= 1)
		return (0);
	if (n == 2)
		return (2);
	while (i * i < n)
	{
		if (n % i == 0)
			return (0);
		i++;
	}
	return (1);
	
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int res;

	sign = 1;
	i = 0;
	res = 0;
	if (str[i] >= '0' && str[i] <= '9')
	{
		while (str[i] >= '0' && str[i] <= '9')
		{
			res = res * 10 + (str[i] - '0');
			i++;
		}
	}
	return (res * sign);
}

int	main(int argc, char **argv)
{
	int	store;

	store = 0;
	if (argc == 2 && (ft_atoi(&argv[1] > 0)))
	{
		while (ft_atoi(&argv[1]) > 0)
		{
			if (is_prime(ft_atoi(&argv[1])))
				store += ft_atoi(&argv[1]);
			argv--;
		}
		return (store);
	}
	write(1, "0\n", 2);
	return (0);
}