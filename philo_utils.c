/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:03:26 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/01/24 17:34:18 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo_data(t_data *philo, char **av)
{
	philo->n_philo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->n_forks = philo->n_philo;
	if (av[5])
		philo->n_time_to_eat = ft_atoi(av[5]);
	else
		philo->n_time_to_eat = -1;
	check_philo(philo);
}
void	check_philo(t_data *philo)
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
