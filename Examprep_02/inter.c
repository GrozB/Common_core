/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:10:53 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/22 09:56:04 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	is_already_printed(char c, char *str, int len)
{
	int	k;

	k = len - 1;
	while (k >= 0)
	{
		if (str[k] == c)
			return (1);
		k--;
	}
	return (0);
}

void	compare_and_print(char *str1, char *str2)
{
	int	i;
	int	j;

	i = 0;
	while (str1[i] != '\0')
	{
		j = 0;
		while (str2[j] != '\0')
		{
			if (str2[j] == str1[i])
			{
				if (!is_already_printed(str1[i], str1, i))
				{
					write(1, &str1[i], 1);
					break ;
				}
			}
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		compare_and_print(argv[1], argv[2]);
	}
	write(1, "\n", 1);
	return (0);
}
