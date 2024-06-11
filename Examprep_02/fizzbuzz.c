/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fizzbuzz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 08:51:50 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/20 09:22:19 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	mini_putnbr(int i)
{
	char	*str;

	str = "0123456789";
	if (i > 9)
		mini_putnbr(i / 10);
	write (1, &str[i % 10], 1);
}

int	main(void)
{
	int	i;

	i = 1;
	while (i != 101)
	{
		if ((i % 3 == 0) && (i % 5 == 0))
			write(1, "fizzbuzz", 8);
		else if (i % 3 == 0)
			write(1, "fizz", 4);
		else if (i % 5 == 0)
			write(1, "buzz", 4);
		else
			mini_putnbr(i);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
