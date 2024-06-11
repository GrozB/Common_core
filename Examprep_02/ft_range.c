/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:46:26 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/25 10:19:01 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int     *ft_range(int start, int end)
{
	int	*array;
	int	i;
	int	len = abs(start -end) + 1;
	
	i = 0;
	array = malloc(sizeof(int) * len);
	if (!array)
		return (NULL);
	while(i < len)
	{
		if (start < end)
		{
			array[i] = start;
			i++;
			start++;
		}
		else
		{
				array[i] = start;
				i++;
				start--;
		}
	}
	return (array);
}
#include <stdio.h>

int main(void)
{
	int	min;
	int	max;
	int	*tab;
	int	i = 0;
	int	size;

	min = -1;
	max = -3;
	size = abs(max - min);
	tab = ft_range(min, max);
	while(i <= size)
	{
		printf("%d, ", tab[i]);
		i++;
	}
}