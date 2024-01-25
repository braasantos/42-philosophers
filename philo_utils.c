/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:03:26 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/01/25 10:09:49 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(int n)
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
	if (n == 6)
		printf("Error\n");
	exit(1);
}
void	parse_args(t_data *data, char **av)
{
	data->n_philo = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	data->starting_time = get_time();
	if (av[5])
		data->n_time_to_eat = ft_atol(av[5]);
	else
		data->n_time_to_eat = -1;
}
int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

long	ft_atol(const char *nptr)
{
	long	num;

	num = 0;
	while (*nptr)
	{
		if (!ft_isdigit(*nptr))
			return (18);
		num = num * 10 + *nptr - 48;
		nptr++;
	}
	if ((num  > 2147483647) || (num  < -2147483648))
		return (18);
	return (num);
}
