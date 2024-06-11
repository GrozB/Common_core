/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:56:39 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/20 13:10:31 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrev(char *str)
{
	int		i;
	int		end;
	char	temp;

	end = 0;
	while (str[end] != '\0')
		end++;
	end--;
	i = 0;
	while (i < end)
	{
		temp = str[i];
		str[i] = str[end];
		str[end] = temp;
		i++;
		end--;
	}
	return (str);
}
/*
int	main(void)
{
	char	str[] = "";
	printf("The string is:%s\n", ft_strrev(str));
}*/
