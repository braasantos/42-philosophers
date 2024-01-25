/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:03:18 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/01/25 10:08:33 by braasantos       ###   ########.fr       */
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
# include <limits.h>

typedef struct s_data t_data;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
}			t_opcode;
/*
* estrutura para os garfos
*/
typedef struct s_fork
{
	pthread_mutex_t fork;
	int				fork_id;
}				t_fork;
 /*
 * essa estrutura representa um philosopher
 */

typedef struct s_philo
{
	pthread_t		thread;
	int				philo_id;
	int				hungry;
	long			last_meal;
	int				count_meals;
	pthread_mutex_t	philo_mutex;
	t_data			*data;
	t_fork	*l_fork; // first
	t_fork	*r_fork; // second
}				t_philo;
/* 
* essa represnta a informacao do programa
*/
typedef struct s_data
{
	pthread_mutex_t	mutex;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	write_mutex;
	pthread_t		monitor;
	long				n_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				n_time_to_eat;
	size_t			starting_time;
	int				all_ready;
	int				end_time;
	t_philo			*philosopher;
	t_fork			*forks;
}				t_data;

/*
* ERROR
*/
void	print_error(int n);

/*
* INIT
*/
void	get_forks(t_philo *philo, t_fork *forks, int position);
void	init_philo(t_data *data);
void	data_init(t_data *data);

/*
* PHILOSOPHERS
*/
void	create_thread(t_data *data);
void	*philo(void *arg);
void	wait_all(t_data *data);
void	ft_thinking(t_philo *philo);
void	ft_eat(t_philo *philo);

/*
* CHECKERS
*/
void	check_args(char **av, t_data *data);


/*
* SAFE
*/
void	*safe_malloc(size_t bytes);
void	safe_mutex(pthread_mutex_t *mutex, t_opcode opcode);
void	safe_pthread(pthread_t *thread, void *(*args)(void *),
		void *data, t_opcode opcode);
/*
* UTILS	
*/
int		ft_isdigit(int c);
void	ft_status(int n, t_philo *philo);
long	ft_atol(const char *nptr);
long	get_time(void);
void	ft_usleep(long time);
void	ft_status(int n, t_philo *philo);
void	parse_args(t_data *data, char **av);

#endif