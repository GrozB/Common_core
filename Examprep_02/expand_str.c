/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:08:17 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/24 15:43:41 by bgroz            ###   ########.fr       */
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
	int	i;
	int	j;
	
	i = 0;
	if (argc != 2)
	{
		write (1, "\n", 1);
		return (0);
	}
	if (argc == 2)
	{
		j = ft_strlen(argv[1]);
		j--;
		while ((argv[1][i] == ' ' || argv[1][i] == '\t') && argv[1][i] != '\0')
			i++;
		while (argv[1][j] == ' ' || argv[1][i] == '\t')
			j--;
		while (i <= j)
		{
			if (argv[1][i] == ' ' || argv[1][i] == '\t')
			{
				write(1, "   ", 3);
				while (argv[1][i] == ' ' || argv[1][i] == '\t')
					i++;
			}
			write(1, &argv[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);