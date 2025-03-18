/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:23:39 by bgroz             #+#    #+#             */
/*   Updated: 2025/03/18 18:25:52 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid_number(const char *str)
{
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

static int	print_error(const char *msg, int len)
{
	write(2, msg, len);
	return (1);
}

static int	parse_required_args(char **argv, t_data *data)
{
	long long	tmp;

	tmp = ft_atoi(argv[1]);
	if (tmp > INT_MAX || tmp <= 0)
		return (print_error("Error: Invalid argument\n", 24));
	data->num_philos = (int)tmp;
	if (data->num_philos > 200)
		return (print_error("Error: Too many philosophers\n", 29));
	tmp = ft_atoi(argv[2]);
	if (tmp <= 0)
		return (print_error("Error: Invalid argument\n", 24));
	data->time_to_die = tmp;
	tmp = ft_atoi(argv[3]);
	if (tmp <= 0)
		return (print_error("Error: Invalid argument\n", 24));
	data->time_to_eat = tmp;
	tmp = ft_atoi(argv[4]);
	if (tmp <= 0)
		return (print_error("Error: Invalid argument\n", 24));
	data->time_to_sleep = tmp;
	return (0);
}

static int	parse_optional_arg(char **argv, t_data *data)
{
	long long	tmp;

	tmp = ft_atoi(argv[5]);
	if (tmp <= 0)
		return (print_error("Error: Invalid argument\n", 24));
	data->num_eat = (int)tmp;
	return (0);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
		return (print_error("Error: Wrong number of arguments\n", 33));
	if (!is_valid_number(argv[1]) || !is_valid_number(argv[2])
		|| !is_valid_number(argv[3]) || !is_valid_number(argv[4]))
		return (print_error("Error: Invalid argument\n", 24));
	if (argc == 6 && !is_valid_number(argv[5]))
		return (print_error("Error: Invalid argument\n", 24));
	if (parse_required_args(argv, data))
		return (1);
	if (argc == 6)
	{
		if (parse_optional_arg(argv, data))
			return (1);
	}
	else
		data->num_eat = -1;
	return (0);
}
