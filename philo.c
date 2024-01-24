/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:03:08 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/01/24 16:12:16 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("gettimeofday() error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/*inicia os philos com o seu id e chopstick correspondente*/
void	check_philos(t_philo *philos, t_data *dta)
{
	int		i;

	i = 0;
	pthread_mutex_init(&dta->mutex, NULL);
	printf("%d\n", philos->n_philo);
	while (i < philos->n_philo)
	{
		philos[i].philo_id = i + 1;
		philos[i].l_chop = philos->chops[i];
		if (i == 0)
			philos[i].r_chop = philos->chops[philos->n_philo - 1];
		else
			philos[i].r_chop = philos->chops[i - 1];
		i++;
	}
}

void	init_philo(t_philo *philos, char **av)
{
	int	i;
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		init_philo_data(&philos[i], av);
		i++;
	}
}

// void check_philos(t_philo *philos, t_data *dta)
// {
//     int i;

//     i = 0;
//     pthread_mutex_init(&dta->mutex, NULL);
//     while (i < philos[i].n_philo)  // Corrected line
//     {
//         philos[i].philo_id = i + 1;
//         philos[i].l_chop = philos[i].chops[i];
//         if (i == 0)
//             philos[i].r_chop = philos[i].chops[philos[i].n_philo - 1];  // Corrected line
//         else
//             philos[i].r_chop = philos[i].chops[i - 1];
//         i++;
//     }
// }


/* inicia os mutextes dos chops */
void	chops( t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->n_philo)
	{
		pthread_mutex_init(&philos->chops[i], NULL);
		i++;
	}
}

void	ft_eat(t_philo *philo)
{
	int i = 0;
	while (i < philo->n_time_to_eat)
	{
		if (!(philo->philo_id % 2 == 0))
		{
			pthread_mutex_lock(&philo->l_chop);
			printf("philo %d has taken the left chopstick\n", philo->philo_id);
			pthread_mutex_lock(&philo->r_chop);
			printf("philo %d has taken the right chopstick\n", philo->philo_id);
			printf("philo %d is eating.\n", philo->philo_id);
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
			pthread_mutex_unlock(&philo->r_chop);
			pthread_mutex_unlock(&philo->l_chop);
		}
	i++;
	}
}


// void	ft_sleep(t_philo *philo)
// {
// 	printf("philo %d, is sleeping\n", philo->philo_id);
// }

// void	ft_thinking(t_philo *philo)
// {
// 	printf("philo %d, is thinking\n", philo->philo_id);
// }
// void	one_philo(t_data *philo, t_philo *philos)
// {
// 	if (philo->n_philo == 1)
// 	{
// 		printf("philo %d has taken the left chopstick\n", philos->philo_id);
// 		printf("philo %d died\n", philos->philo_id);
// 		free(philo);
// 		free(philos);
// 		exit(1);
// 	}
// 	}

void	*philo(void *arg)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)arg;
	printf("%d\n", philosopher->philo_id);
	printf("%d\n", philosopher->time_to_die);
	printf("%d\n", philosopher->time_to_eat);
	printf("%d\n", philosopher->time_to_sleep);

	while(philosopher->time_to_die > 0)
	{
		ft_eat(philosopher);
		philosopher->time_to_die -= 1;
	}
	return (NULL);
}

void	create_thread(t_philo *philos, t_data *dta)
{
	int			i;

	i = 0;
	// one_philo(dta, philos);
	while (i < philos->n_philo)
	{
		pthread_create(&philos[i].thread, NULL, philo, &philos[i]);
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < philos->n_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	
    pthread_mutex_destroy(&dta->mutex);
}

int	main(int ac, char **av)
{
	t_data	dta;
	t_philo	philos;

	if (ac < 4 || ac > 6)
		return (printf("Wrong Number of Arguments\n"));
	init_philo(philos, av);
	check_philos(&philos, &dta);
	chops(&philos);
	create_thread(&philos, &dta);
	return (0);
}



