/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:33:58 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/28 13:24:23 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	get_char_value(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	i;
	int	sign;
	int	res;
	int	value;

	i = 0;
	res = 0;
	value = 0;
	sign = 1;
	if (str_base > 16 || str_base < 2)
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		value = get_char_value(str[i]);
		if (value < 0 || value >= str_base)
			break ;
		res = res * str_base + value;
		i++;
	}
	return (res * sign);
}
#include <stdio.h>
int main()
{
    char *str = "10101";
    int num;

    num = ft_atoi_base(str, 2);
    printf("%d", num);

}