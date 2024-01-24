/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:03:18 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/01/24 16:05:08 by bjorge-m         ###   ########.fr       */
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
# define PHILO_MAX 300

typedef struct s_philo
{
	pthread_t		thread;
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_time_to_eat;
	int				philo_id;
	size_t			hungry;
	size_t			time;
	pthread_mutex_t	chops[PHILO_MAX];
	pthread_mutex_t	l_chop;
	pthread_mutex_t	r_chop;
}				t_philo;

typedef struct s_data
{
	pthread_mutex_t	mutex;
	t_philo			*philosopher;
	int				dead;
}				t_data;

int		ft_isdigit(int c);
size_t	get_time(void);
void	init_philo(t_philo *philos, char **av);
int		ft_atoi(const char *nptr);
void	check_philo(t_philo *philo);
void	free_exit(t_philo *philo, int n);
void	free_exit(t_philo *philo, int n);
void	chops(t_philo *philos);
// void	one_philo(t_data *philo, t_philo *philos);
void	init_philo_data(t_philo *philo, char **av);

#endif
