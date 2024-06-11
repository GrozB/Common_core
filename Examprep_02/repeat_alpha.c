/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:30:14 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/20 09:53:50 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	repeat_alpha(char *str)
{
	int	count;

	if (*str >= 'a' && *str <= 'z')
	{
		count = *str - 'a' + 1;
		while (count > 0)
		{
			write(1, str, 1);
			count--;
		}
	}
	else if (*str >= 'A' && *str <= 'Z')
	{
		count = *str - 'A' + 1;
		while (count > 0)
		{
			write(1, str, 1);
			count--;
		}
	}
	else
		write(1, str, 1);
}

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc == 2)
	{
		while (argv[1][i])
		{
			repeat_alpha(&argv[1][i]);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
