/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6-observer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:31:33 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/01/29 14:53:29 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*control_philos(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
		if (check_dead(data) == 1 || check_n_meals(data) == 1)
			return (NULL);
	return (NULL);
}

int	check_dead(t_data *data)
{
	size_t	curr_time;
	size_t	i;

	i = 0;
	while (i < data->n_philo)
	{
		safe_mutex(&data->philosopher[i].philo_mutex, LOCK);
		curr_time = get_time() - data->philosopher[i].last_meal;
		if (curr_time >= data->philosopher[i].data->time_to_die)
		{
			ft_status(0, data->philosopher);
			safe_mutex(&data->death_mutex, LOCK);
			data->died = 1;
			safe_mutex(&data->death_mutex, UNLOCK);
			safe_mutex(&data->philosopher[i].philo_mutex, UNLOCK);
			return (1);
		}
		safe_mutex(&data->philosopher[i].philo_mutex, UNLOCK);
		i++;
	}
	return (0);
}

int	check_n_meals(t_data *data)
{
	size_t	j;

	j = -1;
	if (data->n_time_to_eat == j)
		return (0);
	safe_mutex(&data->death_mutex, LOCK);
	if (data->all_ate == data->n_philo)
	{
		safe_mutex(&data->death_mutex, UNLOCK);
		return (1);
	}
	safe_mutex(&data->death_mutex, UNLOCK);
	return (0);
}

void	join_threads(t_data *data)
{
	size_t	i;

	i = 0;
	safe_pthread(&data->observer, NULL, NULL, JOIN);
	while (i < data->n_philo)
	{
		safe_pthread(&data->philosopher[i].thread, NULL, NULL, JOIN);
		usleep(1000);
		i++;
	}
}
