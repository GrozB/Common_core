/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:12:21 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/25 13:20:52 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int    lcm(unsigned int a, unsigned int b)
{
	unsigned int	i;
	
	i = 2;
	while (i < (a * b))
	{
		if (a % i == 0 && b % i == 0)
			break ;
		i++;
	}
	return (i);
}
#include <stdio.h>
int	main(void)
{
	unsigned int	a = 5;
	unsigned int	b = 8;

	printf("The result is:%d", lcm(a, b));
}