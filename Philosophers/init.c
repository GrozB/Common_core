/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:07:43 by bgroz             #+#    #+#             */
/*   Updated: 2025/03/18 18:32:31 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
	{
		write(2, "Error: Fork allocation failed\n", 30);
		return (1);
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			write(2, "Error: Mutex init failed\n", 26);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		write(2, "Error: Print mutex init failed\n", 32);
		return (1);
	}
	if (pthread_mutex_init(&data->stop_mutex, NULL) != 0)
	{
		write(2, "Error: Stop mutex init failed\n", 31);
		return (1);
	}
	return (0);
}

static int	init_one_philo(t_data *data, int i)
{
	data->philos[i].id = i + 1;
	data->philos[i].data = data;
	data->philos[i].last_meal = data->start_time;
	data->philos[i].meals_eaten = 0;
	pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
	data->philos[i].left_fork = &data->forks[i];
	if (i == data->num_philos - 1)
		data->philos[i].right_fork = &data->forks[0];
	else
		data->philos[i].right_fork = &data->forks[i + 1];
	if (pthread_create(&data->philos[i].thread, NULL,
			philosopher_routine, &data->philos[i]) != 0)
		return (1);
	return (0);
}

int	create_philosophers(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
	{
		write(2, "Error: Philosopher allocation failed\n", 37);
		return (1);
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (init_one_philo(data, i))
			return (1);
		i++;
	}
	return (0);
}

void	join_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
