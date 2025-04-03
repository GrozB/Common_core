/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:00:45 by bgroz             #+#    #+#             */
/*   Updated: 2025/03/22 17:09:04 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;
	long long		ms;

	gettimeofday(&tv, NULL);
	ms = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	return (ms);
}

void	ft_usleep(long long time_in_ms, t_data *data)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time_in_ms)
	{
		pthread_mutex_lock(&data->stop_mutex);
		if (data->stop)
		{
			pthread_mutex_unlock(&data->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->stop_mutex);
		usleep(100);
	}
}

void	print_action(t_philo *philo, char *action)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (philo->data->stop == 0)
	{
		time = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", time, philo->id, action);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	get_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->stop_mutex);
	stop = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stop);
}
