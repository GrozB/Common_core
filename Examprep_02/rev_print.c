/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:00:35 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/20 10:17:23 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	int		i;
	int		end;
	char	temp;

	if (argc == 2)
	{
		i = 0;
		end = ft_strlen(argv[1]) - 1;
		while (i < end)
		{
			temp = argv[1][i];
			argv[1][i] = argv[1][end];
			argv[1][end] = temp;
			i++;
			end--;
		}
		write(1, argv[1], ft_strlen(argv[1]));
	}
	write(1, "\n", 1);
	return (0);
}
