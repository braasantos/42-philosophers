/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:03:18 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/01/22 16:13:42 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	pthread_mutex_t	l_chop;
	pthread_mutex_t	r_chop;
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_time_to_eat;
	int				n_forks;
}				t_data;

typedef struct s_philo
{
	pthread_mutex_t	mutex;
	t_data			*dta;
	int				philo_id;
}				t_philo;

int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
void	free_exit(t_data *philo);
void	init_philo_data(t_data *philo, char **av, int ac);

#endif
