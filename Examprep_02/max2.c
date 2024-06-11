/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:47:39 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/25 13:55:23 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		max(int* tab, unsigned int len)
{
	unsigned int	i = 0;
	int	store;
	
	if (len == 0)
		return (0);
	store = tab[i];
	while (i < len)
	{
		if (tab[i] > store)
			store = tab[i];
		i++;
	}
	return (store);
}
#include <stdio.h>
int	main(void)
{
	int	tab[] = {0,1,2,3,4,5,6,7,8};
	int	len = 9;
	printf("the solution is:%d", max(tab, len));
}