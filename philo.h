/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:03:18 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/01/24 17:34:07 by braasantos       ###   ########.fr       */
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
	pthread_mutex_t	l_chop;
	pthread_mutex_t	r_chop;
	pthread_t		thread;
	int				hungry;
	int				think;
	int				tired;
	t_data			*dta;
	int				philo_id;
}				t_philo;

int		ft_isdigit(int c);
void	free_exit(t_data *philo, int n);
int		ft_atoi(const char *nptr);
void	check_philo(t_data *philo);
void	chop(t_philo *philos, t_data *dta);
// void	one_philo(t_data *philo, t_philo *philos);
void	init_philo_data(t_data *philo, char **av);

#endif
