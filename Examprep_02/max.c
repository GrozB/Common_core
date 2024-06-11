/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:00:04 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/24 10:06:21 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	max(int* tab, unsigned int len)
{
	unsigned int	i;

	i = 0;
	int	store = 0;
	if (len == 0)
		return (0);
	store = tab[0];
	while (i < len)
	{
		if (store < tab[i])
			store = tab[i];
		i++;
	}
	return (store);
}
#include <stdio.h>
int main() 
{
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    unsigned int len = sizeof(arr) / sizeof(arr[0]);

    int max_value = max(arr, len);
    printf("The maximum value in the array is: %d\n", max_value);
    return (0);
}