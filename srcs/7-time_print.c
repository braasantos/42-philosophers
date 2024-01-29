/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7-time_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:34:38 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/01/29 14:35:47 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		printf("gettimeofday() error\n");
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

size_t	ft_usleep(size_t time)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time * 1e3);
	return (0);
}

void	ft_status(int n, t_philo *philo)
{
	size_t	curr_time;

	safe_mutex(&philo->data->mutex, LOCK);
	if (philo->data->died >= 1 || philo->data->all_ate == philo->data->n_philo)
	{
		safe_mutex(&philo->data->mutex, UNLOCK);
		return ;
	}
	safe_mutex(&philo->data->mutex, UNLOCK);
	curr_time = get_time() - philo->data->starting_time;
	safe_mutex(&philo->data->write_mutex, LOCK);
	if (n == 1)
		printf("%zu %d has taken a fork\n", curr_time, philo->philo_id);
	else if (n == 3)
		printf("%zu %d is eating\n", curr_time, philo->philo_id);
	else if (n == 4)
		printf("%zu %d is thinking\n", curr_time, philo->philo_id);
	else if (n == 5)
		printf("%zu %d is sleeping\n", curr_time, philo->philo_id);
	else if (n == 0)
		printf("%zu %d died\n", curr_time, philo->philo_id);
	safe_mutex(&philo->data->write_mutex, UNLOCK);
}
