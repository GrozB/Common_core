/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:07:00 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/27 14:33:35 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	if (argc == 2)
	{
		while (argv[1][i] != '\0')
			i++;
		i--;
		while (i >= 0)
		{
			end = i;
			while (argv[1][i] != ' ' && i >= 0)
				i--;
			start = i + 1;
			write(1, &argv[1][start], end - start + 1);
			if (i > 0)
				write(1, " ", 1);
			i--;
		}
		
	}
	write(1, "\n", 1);
	return (0);
}