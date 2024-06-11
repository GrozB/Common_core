/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pgcd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:04:50 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/27 11:00:38 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int	i;
	int	j;
	int	store = 0;
	int	store2 = 0;
	int	tempa;
	int	tempb;
	
	i = 1;
	j = 1;
	tempa = atoi(argv[1]);
	tempb = atoi(argv[2]);
	if (argc == 3)
	{
		while (i <= tempa)
		{
			if (tempa % i == 0)
				store = i;
			i++;
		}
		while (j <= tempb)
		{
			if (tempa % j == 0)
				store2 = j;
			j++;
		}
		while (tempa != tempb)
		{
			if (tempa > tempb)
				tempa -= tempb;
			else
				tempb -= tempa;
		}
	}
	printf("%d\n", tempa);
	return (0);
}