#include "philo.h"

void	init_philo(t_philo *philo, char **av, int ac)
{
	philo->n_philo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->n_forks = philo->n_philo;
	if (philo->n_philo == 18)
		free_exit(philo);
	if (philo->n_forks == 18)
		free_exit(philo);
	if (philo->time_to_die == 18)
		free_exit(philo);
	if (philo->time_to_eat == 18)
		free_exit(philo);
	if (philo->time_to_sleep == 18)
		free_exit(philo);
	if (ac == 6)
	{
		philo->n_time_to_eat = ft_atoi(av[5]);
		if (philo->n_time_to_eat == 18)
			free_exit(philo);
	}
}

void	*eat(void *arg)
{
	t_philo* philo = (t_philo*)arg;
	int	i;

	i = 0;
	while (i < 2)
	{
		printf("philo %d has taken one chopstick\n", philo->n_philo);
		philo->n_forks--;
		i++;
	}
	printf("philo %d is eating\n", philo->n_philo);
	return (NULL);
}
void	create_thread(t_philo *philo)
{
	pthread_t	thread;
	int	i;

	i = 0;
	while (i < philo->n_philo)
	{
		pthread_create(&thread, NULL, eat, (void *)philo);
		i++;
	}
	pthread_join(thread, NULL);
}
void free_exit(t_philo *philo)
{
	printf("Not a valid argument\n");
	printf("Try ./philo <n of philosphers> ");
	printf("<time to die> ");
	printf("<time to eat> ");
	printf("<time to sleep> ");
	printf("<n time to eat>\n");
	free(philo);
	exit(1);
}
int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac < 4 || ac > 6)
		return (printf("Wrong Number of Arguments\n"));
	philo = malloc(sizeof(t_philo));
	init_philo(philo, av, ac);
	create_thread(philo);
	free(philo);
	return (0);
}
