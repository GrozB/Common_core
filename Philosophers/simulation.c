#include "philo.h"

long long get_time(void)
{
    struct timeval tv;
    long long ms;

    gettimeofday(&tv, NULL);
    ms = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
    return ms;
}

static void ft_usleep(long long time_in_ms)
{
    long long start;

    start = get_time();
    while (get_time() - start < time_in_ms)
        usleep(100);
}

static void print_action(t_philo *philo, char *action)
{
    long long time;

    pthread_mutex_lock(&philo->data->print_mutex);
    if (philo->data->stop == 0)
    {
        time = get_time() - philo->data->start_time;
        printf("%lld %d %s\n", time, philo->id, action);
    }
    pthread_mutex_unlock(&philo->data->print_mutex);
}

static void	*philosopher_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (p->data->stop == 0)
	{
		if (p->id % 2 == 0)
		{
			pthread_mutex_lock(p->right_fork);
			if (p->data->stop == 1)
			{
				pthread_mutex_unlock(p->right_fork);
				break ;
			}
			print_action(p, "has taken a fork");
			pthread_mutex_lock(p->left_fork);
			if (p->data->stop == 1)
			{
				pthread_mutex_unlock(p->right_fork);
				pthread_mutex_unlock(p->left_fork);
				break ;
			}
			print_action(p, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(p->left_fork);
			if (p->data->stop == 1)
			{
				pthread_mutex_unlock(p->left_fork);
				break ;
			}
			print_action(p, "has taken a fork");
			pthread_mutex_lock(p->right_fork);
			if (p->data->stop == 1)
			{
				pthread_mutex_unlock(p->left_fork);
				pthread_mutex_unlock(p->right_fork);
				break ;
			}
			print_action(p, "has taken a fork");
		}
		print_action(p, "is eating");
		p->last_meal = get_time();
		ft_usleep(p->data->time_to_eat);
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		p->meals_eaten = p->meals_eaten + 1;
		print_action(p, "is sleeping");
		ft_usleep(p->data->time_to_sleep);
		print_action(p, "is thinking");
	}
	return (NULL);
}

static void *monitor_routine(void *arg)
{
	t_philo *p;
	int i;
	int all_eaten;

	p = (t_philo *)arg;
	while (!p[0].data->stop)
	{
		all_eaten = 1;
		i = 0;
		while (i < p[0].data->num_philos)
		{
			if (get_time() - p[i].last_meal > p[0].data->time_to_die)
			{
				pthread_mutex_lock(&p[0].data->print_mutex);
				if (!p[0].data->stop)
				{
					printf("%lld %d died\n", get_time() - p[0].data->start_time, p[i].id);
					p[0].data->stop = 1;
				}
				pthread_mutex_unlock(&p[0].data->print_mutex);
				return (NULL);
			}
			if (p[0].data->num_eat != -1 && p[i].meals_eaten < p[0].data->num_eat)
				all_eaten = 0;
			i++;
		}
		if (p[0].data->num_eat != -1 && all_eaten)
		{
			pthread_mutex_lock(&p[0].data->print_mutex);
			p[0].data->stop = 1;
			pthread_mutex_unlock(&p[0].data->print_mutex);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}


static int handle_single_philo(t_data *data)
{
	data->stop = 0;
	data->start_time = get_time();
	printf("0 1 has taken a fork\n");
	usleep(data->time_to_die * 1000);
	printf("%lld 1 died\n", get_time() - data->start_time);
	return (0);
}

static int init_forks(t_data *data, pthread_mutex_t **forks)
{
    int i;

    *forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    if (!*forks)
    {
        write(2, "Error: Fork allocation failed\n", 30);
        return (1);
    }
    i = 0;
    while (i < data->num_philos)
    {
        if (pthread_mutex_init(&(*forks)[i], NULL) != 0)
        {
            write(2, "Error: Mutex init failed\n", 26);
            return (1);
        }
        i = i + 1;
    }
    return (0);
}

static int create_philosophers(t_data *data, t_philo **philos, pthread_mutex_t *forks)
{
    int i;

    *philos = malloc(sizeof(t_philo) * data->num_philos);
    if (!*philos)
    {
        write(2, "Error: Philosopher allocation failed\n", 37);
        return (1);
    }
    i = 0;
    while (i < data->num_philos)
    {
        (*philos)[i].id = i + 1;
        (*philos)[i].data = data;
        (*philos)[i].last_meal = data->start_time;
        (*philos)[i].meals_eaten = 0;
        (*philos)[i].left_fork = &forks[i];
        if (i == data->num_philos - 1)
            (*philos)[i].right_fork = &forks[0];
        else
            (*philos)[i].right_fork = &forks[i + 1];
        if (pthread_create(&(*philos)[i].thread, NULL,
                philosopher_routine, &(*philos)[i]) != 0)
        {
            write(2, "Error: Thread creation failed\n", 30);
            return (1);
        }
        i = i + 1;
    }
    return (0);
}

static void join_philosophers(t_data *data, t_philo *philos)
{
    int i;

    i = 0;
    while (i < data->num_philos)
    {
        pthread_join(philos[i].thread, NULL);
        i = i + 1;
    }
}

void cleanup_simulation(t_data *data, t_philo *philos, pthread_mutex_t *forks)
{
    int i;

    i = 0;
    while (i < data->num_philos)
    {
        pthread_mutex_destroy(&forks[i]);
        i = i + 1;
    }
    free(forks);
    free(philos);
}

int start_simulation(t_data *data)
{
	pthread_mutex_t *forks;
	t_philo *philos;
	pthread_t monitor;
	int ret;

	if (data->num_philos == 1)
		return handle_single_philo(data);
	ret = init_forks(data, &forks);
	if (ret)
		return (1);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		write(2, "Error: Print mutex init failed\n", 32);
		free(forks);
		return (1);
	}
	data->stop = 0;
	data->start_time = get_time();
	ret = create_philosophers(data, &philos, forks);
	if (ret)
	{
		free(forks);
		free(philos);
		return (1);
	}
	data->philos = philos;
	data->forks = forks;
	if (pthread_create(&monitor, NULL, monitor_routine, philos) != 0)
	{
		write(2, "Error: Monitor thread creation failed\n", 38);
		return (1);
	}
	pthread_join(monitor, NULL);
	join_philosophers(data, philos);
	cleanup_simulation(data, philos, forks);
	return (0);
}
