/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:03:26 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/01/24 16:05:18 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_exit(t_philo *philo, int n)
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
void	init_philo_data(t_philo *philo, char **av)
{
	philo->n_philo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->time = get_time();
	if (philo->n_philo == 18)
		free_exit(philo, 0);
	if (philo->time_to_die == 18)
		free_exit(philo, 0);
	if (philo->time_to_eat == 18)
		free_exit(philo, 0);
	if (philo->time_to_sleep == 18)
		free_exit(philo, 0);
	if (av[5])
	{
		philo->n_time_to_eat = ft_atoi(av[5]);
		if (philo->n_time_to_eat == 18)
			free_exit(philo, 0);
	}
	else
		philo->n_time_to_eat = -1;
	check_philo(philo);
}
void	check_philo(t_philo *philo)
{
	if (philo->n_philo == 0)
		free_exit(philo, 1);
	if (philo->time_to_die == 0)
		free_exit(philo, 2);
	if (philo->time_to_eat  == 0)
		free_exit(philo, 3);
	if (philo->time_to_sleep == 0)
		free_exit(philo, 4);
	if (philo->n_time_to_eat == 0)
		free_exit(philo, 5);
}
int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (nptr[i])
	{
		if (!ft_isdigit(nptr[i]))
			return (18);
		num = num * 10 + nptr[i] - 48;
		i++;
	}
	return (num);
}
