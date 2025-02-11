#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	num;

	i = 0;
	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		if (num > 2147483647)
			return (-1);
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return ((int)num);
}

int	validate_args(t_data *data)
{
	if (data->num_philos < 1 || data->time_to_die < 1
		|| data->time_to_eat < 1 || data->time_to_sleep < 1)
		return (ERROR);
	if (data->num_meals < 0)
		data->num_meals = -1;
	return (SUCCESS);
}

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	safe_usleep(int milliseconds)
{
	long long	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < milliseconds)
		usleep(500);
}

void	print_status(t_data *data, int id, char *status)
{
	long long	timestamp;

	pthread_mutex_lock(&data->write_lock);
	if (data->simulation_end == 0)
	{
		timestamp = get_current_time() - data->start_time;
		printf("%lld %d %s\n", timestamp, id, status);
	}
	pthread_mutex_unlock(&data->write_lock);
}