/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:03:08 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/01/22 16:19:39 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philos, t_data *dta)
{
	int		i;

	i = 0;
	while (i < dta->n_philo)
	{
		philos[i].philo_id = i + 1;
		philos->dta = dta;
		i++;
	}
	pthread_mutex_init(&philos->mutex, NULL);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	printf("philo %d, is eating\n", philo->philo_id);
	pthread_mutex_unlock(&philo->mutex);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	printf("philo %d, is sleeping\n", philo->philo_id);
	pthread_mutex_unlock(&philo->mutex);
}

void	ft_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	printf("philo %d, is thinking\n", philo->philo_id);
	pthread_mutex_unlock(&philo->mutex);
}

void	*philo(void *arg)
{
	t_philo	*philo;

	(t_philo *)arg;
	philo = arg; 
	ft_eat(philo);
	ft_sleep(philo);
	ft_thinking(philo);
	return (NULL);
}

void	create_thread(t_data *dta, t_philo *philos)
{
	pthread_t	thread;
	int			i;

	i = 0;
	while (i < dta->n_philo)
	{
		pthread_create(&thread, NULL, philo, (void *)&philos[i]);
		i++;
	}
	pthread_join(thread, NULL);
}

void	free_exit(t_data *philo)
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
	t_data	*dta;
	t_philo	*philos;

	if (ac < 4 || ac > 6)
		return (printf("Wrong Number of Arguments\n"));
	dta = malloc(sizeof(t_data));
	init_philo_data(dta, av, ac);
	philos = malloc(sizeof(t_philo) * dta->n_philo);
	init_philo(philos, dta);
	create_thread(dta, philos);
	free(dta);
	free(philos);
	return (0);
}
