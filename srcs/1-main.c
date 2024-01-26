#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac <= 4 || ac > 6)
	{
		print_error(0);
		return (0);
	}
	check_args(av, &data);
	data_init(&data);
	create_thread(&data);
	join_threads(&data);
	clean(&data);
	return (0);
}
