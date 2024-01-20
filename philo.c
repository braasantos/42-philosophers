#include "philo.h"

void	init_philo(t_philo *philo, char **av)
{
	philo->n_philo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->n_time_to_eat = ft_atoi(av[5]);
	philo->n_forks = philo->n_philo;
}

void*	printsum(void* arg)
{
	(void)arg;
	printf("im here\n");
	return (NULL);
}
void	create_thread(void)
{
	pthread_t	thread;
	pthread_create(&thread, NULL, printsum, NULL);
	pthread_join(thread, NULL);

}
int	main(int ac, char **av)
{
	t_philo	*philo;

	if ( ac != 6)
		return (printf("Wrong Number of Arguments\n"),0);
	philo = malloc(sizeof(t_philo));
	init_philo(philo, av);
	create_thread();
	printf("n of philosphers - %d\n", philo->n_philo);
	printf("time to die - %d\n", philo->time_to_die);
	printf("time to eat - %d\n", philo->time_to_eat);
	printf("time to sleep - %d\n", philo->time_to_sleep);
	printf("n of time to eat - %d\n", philo->n_time_to_eat);
	printf("n of forks - %d\n", philo->n_forks);
	free(philo);
	return (0);
}
