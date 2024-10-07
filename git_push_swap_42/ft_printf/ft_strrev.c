/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:20:59 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/07 17:47:35 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrevv(char *str)
{
	int		i;
	int		index;
	char	c;

	index = 0;
	i = 0;
	while (str[index] != '\0')
	{
		index++;
	}
	index--;
	while (i < (index))
	{
		c = str[i];
		str[i] = str[index];
		str[index] = c;
		i++;
		index--;
	}
	return (str);
}
