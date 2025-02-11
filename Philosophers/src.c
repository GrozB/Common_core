#include "philo.h"

int	parse_args(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		return (ERROR);
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_meals = ft_atoi(argv[5]);
	else
		data->num_meals = -1;
	if (validate_args(data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int	init_mutexes(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (ERROR);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (pthread_mutex_destroy(&data->write_lock), ERROR);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			pthread_mutex_destroy(&data->write_lock);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

static int	init_philosophers(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philosopher) * data->num_philos);
	if (!data->philos)
		return (ERROR);
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_meal = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		i++;
	}
	return (SUCCESS);
}

int	init_simulation(t_data *data)
{
	data->simulation_end = 0;
	data->start_time = get_current_time();
	if (init_mutexes(data) == ERROR || init_philosophers(data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void	cleanup(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->write_lock);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	free(data->philos);
}
