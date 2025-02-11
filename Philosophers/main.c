#include "philo.h"

int	main(int argc, char **argv)
{
	printf("1\n");
	t_data	data;

	if (parse_args(argc, argv, &data) == 1)
		return (write(2, "Error: Invalid arguments\n", 25), 1);
	printf("2\n");
	if (init_simulation(&data) == 1)
		return (write(2, "Error: Initialization failed\n", 29), 1);
	printf("3\n");
	if (start_simulation(&data) == 1)
		return (write(2, "Error: Simulation failed\n", 25), 1);
	printf("4\n");
	start_simulation(&data);
	cleanup(&data);
	printf("5\n");
	return (0);
}