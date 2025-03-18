/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:39:37 by bgroz             #+#    #+#             */
/*   Updated: 2025/03/18 18:31:47 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		ret;

	ret = parse_args(argc, argv, &data);
	if (ret)
		return (1);
	ret = start_simulation(&data);
	if (ret)
	{
		write(2, "start_simulation returned an error\n", 35);
		return (1);
	}
	write(1, "Simulation ended successfully!\n", 31);
	return (0);
}
