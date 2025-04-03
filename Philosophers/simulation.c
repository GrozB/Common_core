/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:32:41 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/03 19:51:09 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->data->num_philos == 1)
	{
		print_action(p, "has taken a fork");
		ft_usleep(p->data->time_to_die, p->data);
		return (NULL);
	}
	if (p->id % 2 != 0)
		usleep(1000);
	while (!get_stop(p->data)
		&& (p->data->num_eat == -1 || p->meals_eaten < p->data->num_eat))
	{
		if (philo_cycle(p))
			break ;
	}
	return (NULL);
}

void	cleanup_sim(t_data *data, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->stop_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	free(forks);
	free(philos);
}

static int	init_simulation(t_data *data)
{
	int	ret;

	ret = init_forks(data);
	if (ret)
		return (1);
	ret = init_mutexes(data);
	if (ret)
	{
		free(data->forks);
		return (1);
	}
	data->stop = 0;
	data->start_time = get_time();
	return (0);
}

static int	start_threads(t_data *data, pthread_t *monitor)
{
	if (pthread_create(monitor, NULL, monitor_routine, data->philos) != 0)
	{
		write(2, "Error: Monitor thread creation failed\n", 38);
		return (1);
	}
	return (0);
}

int	start_simulation(t_data *data)
{
	pthread_t	monitor;
	int			ret;

	ret = init_simulation(data);
	if (ret)
		return (1);
	ret = create_philosophers(data);
	if (ret)
	{
		free(data->forks);
		free(data->philos);
		return (1);
	}
	if (start_threads(data, &monitor))
		return (1);
	pthread_join(monitor, NULL);
	join_philosophers(data);
	cleanup_sim(data, data->philos, data->forks);
	return (0);
}
