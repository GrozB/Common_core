/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:29:12 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/24 09:52:43 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "do_op2.h"

int	operators(int sign1, int operator, int sign2)
{
	int	i;

	i = 0;
	if (operator == '*')
		i = sign1 * sign2;
	else if (operator == '%')
		i = sign1 % sign2;
	else if (operator == '/')
		i = sign1 / sign2;
	else if (operator == '+')
		i = sign1 + sign2;
	else if (operator == '-')
		i = sign1 - sign2;
	else
		return (0);
	return (i);
}

int	main(int argc, char **argv)
{
	if (argc == 4)
	{
		printf("The result is:%d", operators(atoi(argv[1]), argv[2][0], atoi(argv[3])));
	}
	else
		write(1, "\n", 1);
	return (0);
}