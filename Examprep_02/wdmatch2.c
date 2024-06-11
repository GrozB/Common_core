/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wdmatch2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:48:39 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/24 13:07:54 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	is_in_there(char *str1, char *str2)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (str2[i] != '\0' && str1[j] != '\0')
	{
		if (str1[j] == str2[i])
		{
			j++;
		}
		i++;
	}
	if (str1[j] == '\0')
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	int	i;
	
	i = 0;
	if (argc == 3)
	{
		if (is_in_there(argv[1], argv[2]))
		{
			while (argv[1][i] != '\0')
			{
				write(1, &argv[1][i], 1);
				i++;
			}
			write (1, "\n", 1);
			return (0);
		}
	}
	write(1, "\n", 1);
	return (0);
}