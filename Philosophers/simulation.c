#include "philo.h"

static void	eat(t_philosopher *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = (philo->id % philo->data->num_philos);

	if (philo->id % 2 == 0)  // Even philosophers take the right fork first
	{
		pthread_mutex_lock(&philo->data->forks[right_fork]);
		print_status(philo->data, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[left_fork]);
	}
	else  // Odd philosophers take the left fork first
	{
		pthread_mutex_lock(&philo->data->forks[left_fork]);
		print_status(philo->data, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[right_fork]);
	}

	print_status(philo->data, philo->id, "is eating");
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	safe_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[right_fork]);
	pthread_mutex_unlock(&philo->data->forks[left_fork]);
}

static void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	philo->last_meal = get_current_time();
	printf("Philosopher %d started\n", philo->id);

	while (1)  // Force it to execute for debugging
	{
		printf("Philosopher %d is in the loop\n", philo->id);

		// REMOVE ANY CONDITIONS
		printf("Philosopher %d about to call eat()\n", philo->id);
		fflush(stdout);  // Ensure output prints immediately

		eat(philo);  // Ensure `eat()` runs!

		print_status(philo->data, philo->id, "is sleeping");
		safe_usleep(philo->data->time_to_sleep);
	}

	printf("Philosopher %d stopped\n", philo->id);
	return (NULL);
}

static void	*monitor_philosophers(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (data->simulation_end == 0)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_lock(&data->write_lock);
			printf("Checking Philosopher %d, last meal: %lld\n", 
				data->philos[i].id, get_current_time() - data->philos[i].last_meal);
			if ((get_current_time() - data->philos[i].last_meal) >= data->time_to_die)
			{
				print_status(data, data->philos[i].id, "died");
				data->simulation_end = 1;
			}
			pthread_mutex_unlock(&data->write_lock);
			if (data->simulation_end)
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}


int	start_simulation(t_data *data)
{
	pthread_t	monitor;
	int			i;

	if (pthread_create(&monitor, NULL, monitor_philosophers, data) != 0)
		return (write(2, "Error: Monitoring thread failed\n", 32), ERROR);
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].last_meal = get_current_time();
		if (pthread_create(&data->philos[i].thread, NULL,
				philosopher_routine, &data->philos[i]) != 0)
			return (write(2, "Error: Thread creation failed\n", 30), ERROR);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	return (SUCCESS);
}
