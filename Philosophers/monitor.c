/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:06:39 by bgroz             #+#    #+#             */
/*   Updated: 2025/03/22 17:09:21 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	report_death(t_philo *p, int i)
{
	pthread_mutex_lock(&p[0].data->print_mutex);
	pthread_mutex_lock(&p[0].data->stop_mutex);
	if (!p[0].data->stop)
	{
		printf("%lld %d died\n", get_time() - p[0].data->start_time, p[i].id);
		p[0].data->stop = 1;
	}
	pthread_mutex_unlock(&p[0].data->stop_mutex);
	pthread_mutex_unlock(&p[0].data->print_mutex);
}

static int	check_death(t_philo *p)
{
	int			i;
	long long	last;

	i = 0;
	while (i < p[0].data->num_philos)
	{
		pthread_mutex_lock(&p[i].meal_mutex);
		last = p[i].last_meal;
		pthread_mutex_unlock(&p[i].meal_mutex);
		if (get_time() - last > p[0].data->time_to_die)
		{
			report_death(p, i);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_meals(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p[0].data->num_philos)
	{
		pthread_mutex_lock(&p[i].meal_mutex);
		if (p[i].meals_eaten < p[0].data->num_eat)
		{
			pthread_mutex_unlock(&p[i].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&p[i].meal_mutex);
		i++;
	}
	return (1);
}

static int	monitor_iteration(t_philo *p)
{
	if (get_stop(p->data))
		return (1);
	if (check_death(p))
		return (1);
	if (p[0].data->num_eat != -1 && check_meals(p))
	{
		pthread_mutex_lock(&p[0].data->print_mutex);
		pthread_mutex_lock(&p[0].data->stop_mutex);
		p[0].data->stop = 1;
		pthread_mutex_unlock(&p[0].data->stop_mutex);
		pthread_mutex_unlock(&p[0].data->print_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (1)
	{
		if (monitor_iteration(p))
			break ;
		usleep(1000);
	}
	return (NULL);
}
