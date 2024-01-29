/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9-utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:37:00 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/01/29 14:38:29 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
	if ((num > 2147483647) || (num < -2147483648))
		return (18);
	return (num);
}

void	*safe_malloc(size_t bytes)
{
	void	*mlc;

	mlc = malloc(bytes);
	if (mlc == NULL)
		printf("Error with malloc\n");
	return (mlc);
}

void	safe_mutex(pthread_mutex_t *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
	{
		if (pthread_mutex_lock(mutex))
			print_error(6);
	}
	else if (opcode == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex))
			print_error(6);
	}
	else if (opcode == INIT)
	{
		if (pthread_mutex_init(mutex, NULL))
			print_error(6);
	}
	else if (opcode == DESTROY)
	{
		if (pthread_mutex_destroy(mutex))
			print_error(6);
	}
}

void	safe_pthread(pthread_t *thread, void *(*args)(void *),
		void *data, t_opcode opcode)
{
	if (opcode == CREATE)
	{
		if (pthread_create(thread, NULL, args, data))
			print_error(6);
	}
	else if (opcode == JOIN)
	{
		if (pthread_join(*thread, NULL))
			print_error(6);
	}
}
