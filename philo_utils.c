/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:03:26 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/01/22 16:14:30 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo_data(t_data *philo, char **av, int ac)
{
	philo->n_philo = ft_atoi(av[1]);
	if (philo->n_philo <= 0)
		free_exit(philo);
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
