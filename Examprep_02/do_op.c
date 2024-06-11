/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:30:43 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/20 12:52:45 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_operators(int a, int operator, int b)
{
	int	c;

	c = 0;
	if (operator == '*')
		c = a * b;
	else if (operator == '/')
		c = a / b;
	else if (operator == '+')
		c = a + b;
	else if (operator == '-')
		c = a - b;
	else if (operator == '%')
		c = a % b;
	else
		return (0);
	return (c);
}

int	main(int argc, char **argv)
{
	int	tempa;
	int	tempb;

	if (argc == 4)
	{
		tempa = atoi(argv[1]);
		tempb = atoi(argv[3]);
		printf("Your result is:%d\n", ft_operators(tempa, argv[2][0], tempb));
	}
	else
		write(1, "\n", 1);
	return (0);
}
