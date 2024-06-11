/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidenp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 10:32:49 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/25 10:41:41 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	if (argc == 3)
	{
		while (argv[1][i])
		{
			while (argv[2][j])
			{
				if (argv[1][i] == argv[2][j])
				{
					i++;
					break ;
				}
				j++;
			}
			if (argv[2][j] == '\0')
			{
				write(1, "0\n", 2);
				return (0);
			}
		}
		if (argv[1][i] == '\0')
			{
				write(1, "1\n", 2);
				return (0);
			}
	}
	write(1, "\n", 1);
	return (0);
}