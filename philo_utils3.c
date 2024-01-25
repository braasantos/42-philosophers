/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:11:22 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/01/25 10:20:19 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_mutex(pthread_mutex_t *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
	{
		if (pthread_mutex_lock(mutex) != 0)
			print_error(6);
	}
	else if (opcode == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex) != 0)
			print_error(6);
	}
	else if (opcode == INIT)
	{
		if (pthread_mutex_init(mutex, NULL) != 0)
			print_error(6);
	}
	else if (opcode == DESTROY)
	{
		if (pthread_mutex_destroy(mutex) != 0)
			print_error(6);
	}
	else
		print_error(6);
}

void	safe_pthread(pthread_t *thread, void *(*args)(void *),
		void *data, t_opcode opcode)
{
	if (opcode == CREATE)
	{
		if(pthread_create(thread, NULL, args, data) != 0)
			print_error(6);
	}
	else if (opcode == JOIN)
	{
		if (pthread_join(*thread, NULL) != 0)
			print_error(6);
	}
	else
		print_error(6);
}
