/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5-forks.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:30:44 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/01/29 14:30:57 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	drop_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		safe_mutex(&philo->l_fork->fork, UNLOCK);
		safe_mutex(&philo->r_fork->fork, UNLOCK);
	}
	else
	{
		safe_mutex(&philo->r_fork->fork, UNLOCK);
		safe_mutex(&philo->l_fork->fork, UNLOCK);
	}
}

int	grab_forks(t_philo *philo)
{
	safe_mutex(&philo->data->mutex, LOCK);
	if (philo->data->died >= 1 || philo->data->all_ate == philo->data->n_philo)
	{
		safe_mutex(&philo->data->mutex, UNLOCK);
		return (1);
	}
	safe_mutex(&philo->data->mutex, UNLOCK);
	if (philo->philo_id % 2 == 0)
	{
		safe_mutex(&philo->r_fork->fork, LOCK);
		ft_status(1, philo);
		safe_mutex(&philo->l_fork->fork, LOCK);
		ft_status(1, philo);
	}
	else
	{
		safe_mutex(&philo->l_fork->fork, LOCK);
		ft_status(1, philo);
		safe_mutex(&philo->r_fork->fork, LOCK);
		ft_status(1, philo);
	}
	return (0);
}
