#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define ERROR 1
# define SUCCESS 0

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	long long		last_meal;
	int				meals_eaten;
	struct s_data	*data;
}	t_philosopher;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	int				simulation_end;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	t_philosopher	*philos;
}	t_data;

int		parse_args(int argc, char **argv, t_data *data);
int		init_simulation(t_data *data);
int		start_simulation(t_data *data);
void	cleanup(t_data *data);
long long	get_current_time(void);
void		safe_usleep(int milliseconds);
void		print_status(t_data *data, int id, char *status);
int		ft_atoi(const char *str);
int		validate_args(t_data *data);

#endif
