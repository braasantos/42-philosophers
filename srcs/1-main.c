/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:27:02 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/01/29 14:27:03 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
	join_threads(&data);
	clean(&data);
	return (0);
}
