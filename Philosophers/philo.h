/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:26:16 by bgroz             #+#    #+#             */
/*   Updated: 2025/03/18 18:30:40 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				num_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				num_eat;
	long long		start_time;
	int				stop;
	pthread_mutex_t	print_mutex;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	stop_mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long long		last_meal;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
	pthread_mutex_t	meal_mutex;
}	t_philo;

long long	ft_atoi(const char *str);
long long	get_time(void);
int			start_simulation(t_data *data);
void		cleanup_sim(t_data *data, t_philo *philos, pthread_mutex_t *forks);
int			parse_args(int argc, char **argv, t_data *data);
void		ft_usleep(long long time_in_ms);
void		print_action(t_philo *philo, char *action);
int			init_forks(t_data *data);
int			init_mutexes(t_data *data);
int			philo_cycle(t_philo *p);
void		join_philosophers(t_data *data);
void		*monitor_routine(void *arg);
int			create_philosophers(t_data *data);
void		*philosopher_routine(void *arg);
int			get_stop(t_data *data);

#endif
