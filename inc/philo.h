
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
	DETACH,
}			t_opcode;
/*
* Struct for a single fork
*/
typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}				t_fork;

/*
* Struct for a single philosopher 
*/
typedef struct s_philo
{
	int				philo_id;
	size_t			last_meal;
	int				meals_count;
	int				dead;
	t_data			*data;
	pthread_t		thread;
	t_fork	*l_fork;
	t_fork	*r_fork;
}				t_philo;

/* 
* Struct for all the info of the program
*/
typedef struct s_data
{
	pthread_mutex_t	mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	_mutex;
	pthread_t		observer;
	size_t				n_philo;
	int					died;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				n_time_to_eat;
	size_t			starting_time;
	size_t				end_time;
	t_philo			*philosopher;
	t_fork			*forks;
}				t_data;


/*
* Check the command line arguments and initialize the data struct
*/
void	check_args(char **av, t_data  *data);
void	parse_args(t_data *data, char **av);

/*
* Print error messages based on the number given
*/
void	print_error(int n);

/*
* Utils
*/
int	ft_isdigit(int c);
long	ft_atol(const char *nptr);

/*
* Init the data structure, malloc the array of philosophers 
* and forks and initialize the mutexes on the array of forks 
*/
void	data_init(t_data *data);

/*
* Init the philo struct with al the 
* necessary data for each philosopher
*/
void	init_philo(t_data *data);

/*
* Determines which forks a philosopher
* should use based on their position and ID.
*/
void	get_forks(t_philo *philo, t_fork *forks, int position);

/*
* Helps to avoid malloc, threads and mutex problems
*/
void	*safe_malloc(size_t bytes);
void	safe_mutex(pthread_mutex_t *mutex, t_opcode opcode);
void	safe_pthread(pthread_t *thread, void *(*args)(void *),
		void *data, t_opcode opcode);
/*
* Create the thread for each philosopher
*/
void	create_thread(t_data *data);

/*
* The routine funtion and the action function "Think" "Eat"
*/
void	*philo(void *arg);
void	ft_thinking(t_philo *philo);
void	ft_eat(t_philo *philo);

/*
* Write the current status of the philosopher
*/
void	ft_status(int n, t_philo *philo);

/*
* Cleans everuthing after the program executed
*/
void	clean(t_data *data);

/*
* A Function to get the time in milisecods
*/
size_t	get_time(void);

/* 
* Precise usleep that recieves the time in miliseconds
* and converts to microseconds so that usleep works
*/
size_t	ft_usleep(size_t time);

/*
* Observer function to make sure they are doing 
* what they are supposed to do
*/
void	*control_philos(void *arg);

/*
* Check if a philosopher is dead based on conditions
*/
int	check_dead(t_data *data);

/*
* Join all threads created
*/
void	join_threads(t_data *data);
#endif
