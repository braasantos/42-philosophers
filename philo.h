#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct	s_philo
{
  int	philo_id;
}				t_philo;
typedef struct	s_philodata
{
  int		n_philo;
  int		time_to_die;
  int		time_to_eat;
  int		time_to_sleep;
  int		n_time_to_eat;
  int		n_forks;
  t_philo	*philosopher;
}				t_philodata;



int	ft_isdigit(int c);
int	ft_atoi(const char *nptr);
void free_exit(t_philodata *philo);
#endif