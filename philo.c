#include "philo.h"

void init_philo(t_philodata *philo_data) {
    t_philo *philosopher;
    int i;

    i = 0;
    philosopher = malloc(sizeof(t_philo) * philo_data->n_philo);
    while (i < philo_data->n_philo) {
        philosopher[i].philo_id += i;
        i++;
    }
    philo_data->philosopher = philosopher;
}


void	init_philo_data(t_philodata *philo, char **av, int ac)
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
	t_philodata* philo = (t_philodata*)arg;
	int	i;

	i = 0;
	while (i < 2)
	{
		printf("philo %d has taken one chopstick\n",philo->philosopher[i].philo_id);
		philo->n_forks--;
		i++;
	}
	printf("philo %d is eating\n", philo->philosopher[i].philo_id);
	return (NULL);
}
void	create_thread(t_philodata *philo)
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
void free_exit(t_philodata *philo)
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
	t_philodata	*philo;

	if (ac < 4 || ac > 6)
		return (printf("Wrong Number of Arguments\n"));
	philo = malloc(sizeof(t_philodata));
	init_philo_data(philo, av, ac);
	init_philo(philo);
	create_thread(philo);
	free(philo);
	return (0);
}
