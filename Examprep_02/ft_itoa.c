/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:11:25 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/28 12:48:19 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_itoa(int nbr)
{
	int	len = 0;
	int	n = nbr;
	char	*res;

	if (nbr == -2147483648)
	{
		res = malloc(sizeof(char) * 12);
		if (res != NULL)
		{
			res[0] = '-';
			res[1] = '2';
			res[2] = '1';
			res[3] = '4';
			res[4] = '7';
			res[5] = '4';
			res[6] = '8';
			res[7] = '3';
			res[8] = '6';
			res[9] = '4';
			res[10] = '8';
			res[11] = '\0';
			return (res);
		}
		return (NULL);
	}
	if (nbr <= 0)
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	res[len] = '\0';
	if (nbr == 0)
	{
		res[0] = '0';
		return (res);
	}
	if (nbr < 0)
	{
		res[0] = '-';
		nbr = -nbr;
	}
	int	index = len - 1;
	while (nbr)
	{
		res[index] = nbr % 10 + '0';
		nbr = nbr / 10;
		index--;
	}
	return (res);
}
#include <stdio.h>
int main(void)
{
    char *str;

    str = ft_itoa(0);
    if (str != NULL)
    {
        printf("%s\n", str);
        free(str);
    }

    str = ft_itoa(42);
    if (str != NULL)
    {
        printf("%s\n", str);
        free(str);
    }

    str = ft_itoa(-2147483648);
    if (str != NULL)
    {
        printf("%s\n", str);
        free(str);
    }

    return 0;
}