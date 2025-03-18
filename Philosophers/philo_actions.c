/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:05:13 by bgroz             #+#    #+#             */
/*   Updated: 2025/03/18 18:14:30 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	acquire_forks_even(t_philo *p)
{
	int	stop;

	pthread_mutex_lock(p->right_fork);
	pthread_mutex_lock(&p->data->stop_mutex);
	stop = p->data->stop;
	pthread_mutex_unlock(&p->data->stop_mutex);
	if (stop)
	{
		pthread_mutex_unlock(p->right_fork);
		return (1);
	}
	print_action(p, "has taken a fork");
	pthread_mutex_lock(p->left_fork);
	pthread_mutex_lock(&p->data->stop_mutex);
	stop = p->data->stop;
	pthread_mutex_unlock(&p->data->stop_mutex);
	if (stop)
	{
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
		return (1);
	}
	print_action(p, "has taken a fork");
	return (0);
}

static int	acquire_forks_odd(t_philo *p)
{
	int	stop;

	pthread_mutex_lock(p->left_fork);
	pthread_mutex_lock(&p->data->stop_mutex);
	stop = p->data->stop;
	pthread_mutex_unlock(&p->data->stop_mutex);
	if (stop)
	{
		pthread_mutex_unlock(p->left_fork);
		return (1);
	}
	print_action(p, "has taken a fork");
	pthread_mutex_lock(p->right_fork);
	pthread_mutex_lock(&p->data->stop_mutex);
	stop = p->data->stop;
	pthread_mutex_unlock(&p->data->stop_mutex);
	if (stop)
	{
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		return (1);
	}
	print_action(p, "has taken a fork");
	return (0);
}

static void	eat_cycle(t_philo *p)
{
	print_action(p, "is eating");
	pthread_mutex_lock(&p->meal_mutex);
	p->last_meal = get_time();
	pthread_mutex_unlock(&p->meal_mutex);
	ft_usleep(p->data->time_to_eat);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_lock(&p->meal_mutex);
	p->meals_eaten++;
	pthread_mutex_unlock(&p->meal_mutex);
}

static void	sleep_and_think_cycle(t_philo *p)
{
	print_action(p, "is sleeping");
	ft_usleep(p->data->time_to_sleep);
	print_action(p, "is thinking");
}

int	philo_cycle(t_philo *p)
{
	if (get_stop(p->data))
		return (1);
	if (p->id % 2 == 0)
	{
		if (acquire_forks_even(p))
			return (1);
	}
	else
	{
		if (acquire_forks_odd(p))
			return (1);
	}
	eat_cycle(p);
	sleep_and_think_cycle(p);
	return (0);
}
