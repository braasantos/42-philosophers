/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:03:08 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/01/23 16:39:44 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
size_t	get_time(t_data *data)
{
	if (gettimeofday(&data->current_time, NULL) == -1)
		printf("gettimeofday() error\n");
	return (data->current_time.tv_sec * 1000 + data->current_time.tv_usec / 1000);
}
void	init_philo(t_philo *philos, t_data *dta)
{
	int		i;

	i = 0;
	philos->hungry = 0;
	while (i < dta->n_philo)
	{
		philos[i].philo_id = i + 1;
		philos[i].dta = dta;
		pthread_mutex_init(&philos[i].mutex, NULL);
        chop(&philos[i], dta);
		i++;
	}
}

void	chop(t_philo *philos, t_data *dta)
{
	int		i;

	i = 0;
	while (i < dta->n_philo)
	{
		if (philos->philo_id == 1)
		{
			pthread_mutex_init(&philos[i + 1].l_chop, NULL);
			pthread_mutex_init(&philos[dta->n_philo].r_chop, NULL);
		}
        pthread_mutex_init(&philos[i].l_chop, NULL);
        pthread_mutex_init(&philos[i].r_chop, NULL);
		i++;
	}
}

void	ft_eat(t_philo *philo)
{
	while (1)
	{
		if (philo->hungry == 0)
		{
			if (!(philo->philo_id % 2 == 0))
			{
				pthread_mutex_lock(&philo->l_chop);
				printf("philo %d has taken the left chopstick\n", philo->philo_id);
				pthread_mutex_lock(&philo->r_chop);
				printf("philo %d has taken the right chopstick\n", philo->philo_id);
				printf("Philo %d is eating.\n", philo->philo_id);
				pthread_mutex_unlock(&philo->l_chop);
				pthread_mutex_unlock(&philo->r_chop);
			}
			else
			{
				pthread_mutex_lock(&philo->r_chop);
				printf("philo %d has taken the right chopstick\n", philo->philo_id);
				pthread_mutex_lock(&philo->l_chop);
				printf("philo %d has taken the left chopstick\n", philo->philo_id);
				printf("Philo %d is eating.\n", philo->philo_id);
				pthread_mutex_unlock(&philo->l_chop);
				pthread_mutex_unlock(&philo->r_chop);
			}
			philo->hungry = 1;
			if (philo->hungry == 1)
				return ;
		}
		// philo->dta->n_time_to_eat -= 1;
	}
}


void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_chop);
	printf("philo %d, is sleeping\n", philo->philo_id);
	sleep(0.1);
	pthread_mutex_unlock(&philo->l_chop);
}

void	ft_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	printf("philo %d, is thinking\n", philo->philo_id);
	sleep(0.1);
	pthread_mutex_unlock(&philo->l_chop);
}
void	one_philo(t_data *philo, t_philo *philos)
{
	if (philo->n_philo == 1)
	{
		printf("philo %d has taken the left chopstick\n", philos->philo_id);
		sleep(1);
		printf("philo %d died\n", philos->philo_id);
		free(philo);
		free(philos);
		exit(1);
	}
	}

void	*philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// printf("time to die od philo %d is %d\n", philo->philo_id, philo->dta->time_to_die);
	while(philo->dta->time_to_die > 0)
	{
		philo->hungry = 0;
		ft_eat(philo);
		philo->dta->time_to_die -= 1;
		// printf("time to die od philo %d is %d\n", philo->philo_id, philo->dta->time_to_die);
	}
	return (NULL);
}

void	create_thread(t_data *dta, t_philo *philos)
{
	int			i;

	i = 0;
	one_philo(dta, philos);
	while (i < dta->n_philo)
	{
		pthread_create(&philos[i].thread, NULL, philo, (void *)&philos[i]);
		i++;
	}
	pthread_join(philos->thread, NULL);
    pthread_mutex_destroy(&philos->mutex);
}

void	free_exit(t_data *philo, int n)
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
	free(philo);
	exit(1);
}

int	main(int ac, char **av)
{
	t_data	*dta;
	t_philo	*philos;

	if (ac < 4 || ac > 6)
		return (printf("Wrong Number of Arguments\n"));
	dta = malloc(sizeof(t_data));
	init_philo_data(dta, av, ac);
	philos = malloc(sizeof(t_philo) * dta->n_philo);
	init_philo(philos, dta);
	dta->time = get_time(dta);
	// printf("time: %ld miliseconds\n", dta->time);
	create_thread(dta, philos);
	free(dta);
	free(philos);
	return (0);
}
