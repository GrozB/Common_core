#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>


typedef struct s_philo	t_philo;

typedef struct s_data {
    int             num_philos;
    long long       time_to_die;
    long long       time_to_eat;
    long long       time_to_sleep;
    int             num_eat; // -1 if not provided
    long long       start_time;
    int             stop;    // 0 = simulation running, 1 = stop simulation
    pthread_mutex_t print_mutex;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}   t_data;

typedef struct s_philo {
    int             id;
    pthread_t       thread;
    long long       last_meal;
    int             meals_eaten;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data          *data;
}   t_philo;

long long   ft_atoi(const char *str);
long long   get_time(void);
int         start_simulation(t_data *data);
void 		cleanup_simulation(t_data *data, t_philo *philos, pthread_mutex_t *forks);

#endif
