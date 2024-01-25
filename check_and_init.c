/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:11:16 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/01/25 09:57:37 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_args(char **av, t_data  *data)
{
	if (ft_atol(av[1])== 18 || ft_atol(av[1])== 0)
		print_error(1);
	if (ft_atol(av[2])== 18 || ft_atol(av[2])== 0)
		print_error(2);
	if (ft_atol(av[3])== 18 || ft_atol(av[3])== 0)
		print_error(3);
	if (ft_atol(av[4])== 18 || ft_atol(av[4])== 0)
		print_error(4);
	if (av[5])
	{
		if (ft_atol(av[5])== 18 || ft_atol(av[5])== 0)
			print_error(5);
	}
	parse_args(data, av);
}
void	*safe_malloc(size_t bytes)
{
	void	*mlc;
	mlc = malloc(bytes);
	if (mlc == NULL)
		printf("Error with malloc\n");
	return(mlc);
}

void	get_forks(t_philo *philo, t_fork *forks, int position)
{
	philo->l_fork = &forks[(position + 1) % philo->data->n_philo];
	philo->r_fork = &forks[position];
	if (philo->philo_id % 2 == 0)
	{
		philo->l_fork = &forks[position];
		philo->r_fork = &forks[(position + 1) % philo->data->n_philo];
	}
}
void	init_philo(t_data *data)
{
	int		i;
	t_philo *philo;

	i = 0;
	while (i < data->n_philo)
	{
		philo = data->philosopher + i;
		philo->philo_id = i + 1;
		philo->hungry = 0;
		philo->count_meals = 0;
		safe_mutex(&philo->philo_mutex, INIT);
		philo->data = data;
		get_forks(philo, data->forks, i);
		i++;
	}
}
void	data_init(t_data *data)
{
	int	i;

	i = 0;
	data->end_time = 0;
	data->all_ready = 0;
	data->philosopher = safe_malloc(sizeof(t_philo) * data->n_philo);
	data->forks = safe_malloc(sizeof(t_fork) * data->n_philo);
	safe_mutex(&data->data_mutex, INIT);
	safe_mutex(&data->write_mutex, INIT);
	while (i < data->n_philo)
	{
		safe_mutex(&data->forks[i].fork, INIT);
		data->forks[i].fork_id = i;
		i++;
	}
	init_philo(data);
}