#include "philo.h"

static int	parse_args(int argc, char **argv, t_data *data)
{
    long long   tmp;

    if (argc != 5 && argc != 6)
    {
        write(2, "Error: Wrong number of arguments\n", 34);
        return (1);
    }
    tmp = ft_atoi(argv[1]);
    if (tmp > INT_MAX || tmp <= 0)
        return (write(2, "Error: Invalid argument\n", 25), 1);
    data->num_philos = (int)tmp;
    tmp = ft_atoi(argv[2]);
    if (tmp <= 0)
        return (write(2, "Error: Invalid argument\n", 25), 1);
    data->time_to_die = tmp;
    tmp = ft_atoi(argv[3]);
    if (tmp <= 0)
        return (write(2, "Error: Invalid argument\n", 25), 1);
    data->time_to_eat = tmp;
    tmp = ft_atoi(argv[4]);
    if (tmp <= 0)
        return (write(2, "Error: Invalid argument\n", 25), 1);
    data->time_to_sleep = tmp;
    if (argc == 6)
    {
        tmp = ft_atoi(argv[5]);
        if (tmp <= 0)
            return (write(2, "Error: Invalid argument\n", 25), 1);
        data->num_eat = (int)tmp;
    }
    else
        data->num_eat = -1;
    return (0);
}

int main(int argc, char **argv)
{
    t_data data;
    int    ret;

    ret = parse_args(argc, argv, &data);
    if (ret)
        return (1);
    ret = start_simulation(&data);
	if (ret)
	{
		write(2, "start_simulation returned an error\n", 35);
		return (1);
	}
    write(1, "Simulation ended successfully!\n", 31);
    return (0);
}
