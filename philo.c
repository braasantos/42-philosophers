/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:03:08 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/01/25 10:19:51 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("gettimeofday() error\n");
	return (time.tv_sec * 1e3 + time.tv_usec / 1e3); // 1000
}


void	ft_eat(t_philo *philo)
{
	safe_mutex(&philo->l_fork->fork, LOCK);
	ft_status(1, philo);
	safe_mutex(&philo->r_fork->fork, LOCK);
	ft_status(2, philo);
	philo->last_meal = get_time();
	philo->count_meals++;
	ft_status(3, philo);
	ft_usleep(philo->data->time_to_eat);
	if (philo->data->n_time_to_eat > 0 && philo->count_meals == philo->data->n_time_to_eat)
		philo->hungry = 1;
	safe_mutex(&philo->l_fork->fork, UNLOCK);
	safe_mutex(&philo->r_fork->fork, UNLOCK);
}
void	ft_status(int n, t_philo *philo)
{
	long	time = 0;;

	if (philo->hungry == 1)
		return ;
	safe_mutex(&philo->data->write_mutex, LOCK);
	if (n == 1 || n == 2)
		printf("%ld %d has taken a fork\n", time, philo->philo_id);
	else if (n == 3)
		printf("%ld %d is eating\n", time, philo->philo_id);
	else if (n == 4)
		printf("%ld %d is thinking\n", time, philo->philo_id);
	else if (n == 5)
		printf("%ld %d is sleeping\n", time, philo->philo_id);
	else if (n == 0)
		printf("%ld %d died\n", time, philo->philo_id);
	safe_mutex(&philo->data->write_mutex, UNLOCK);
}
void	ft_usleep(long time)
{
	long	start;
	
	start = get_time();
	while (get_time() - start < time)
		usleep(500);
	return ;
}

void	ft_thinking(t_philo *philo)
{
	ft_status(4, philo);
}
void	wait_all(t_data *data)
{
	while(data->all_ready == 0)
		;
}
void	*philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all(philo->data);
	if (philo->philo_id % 2 == 0)
		usleep(1);
	while(1)
	{
		if (philo->hungry == 1)
			break ;
		ft_eat(philo);
		ft_status(5, philo);
		ft_usleep(philo->data->time_to_sleep);
		ft_thinking(philo);
	}
	return (NULL);
}

void	create_thread(t_data *data)
{
	int			i;

	i = -1;
	if(data->n_time_to_eat == 0)
		return ;
	// else if [one philo]
	else 
	{
		while (++i < data->n_philo)
			safe_pthread(&data->philosopher[i].thread, philo, &data->philosopher[i], CREATE);
	}
	// safe_pthread(&data->monitor, control_philos, data, CREATE);
	data->starting_time = get_time();
	data->all_ready = 1;
	i = 0;
	while (i < data->n_philo)
	{
		safe_pthread(&data->philosopher[i].thread, NULL, NULL, JOIN);
		i++;
	}
	data->all_ready = 0;
	// pthread_mutex_destroy(&data->mutex);

}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac <= 4 || ac > 6)
	{
		print_error(0);
		return (0);
	}
	check_args(av, &data);
	data_init(&data);
	create_thread(&data);
	return (0);
}
