#include "../inc/philo.h"

void	print_error(int n)
{
	if (n == 0)
	{
		printf("Not a valid argument\n");
		printf("Try ./philo <n of philosphers> ");
		printf("<time to die> ");
		printf("<time to eat> ");
		printf("<time to sleep> ");
		printf("<n time to eat>\n");
	}
	if (n == 1)
		printf("Invalid Philosopher\n");
	if (n == 2)
		printf("Invalid time to die\n");
	if (n == 3)
		printf("Invalid time to eat\n");
	if (n == 4)
		printf("Invalid time to sleep\n");
	if (n == 5)
		printf("Invalid time every philosopher must eat\n");
	if (n == 6)
		printf("Error\n");
	exit(1);
}

void	clean(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->n_philo)
	{	
		safe_mutex(&data->forks[i].fork, DESTROY);
		i++;
	}
	safe_mutex(&data->write_mutex, DESTROY);
	free(data->forks);
	free(data->philosopher);
	exit(0);
}
