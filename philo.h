#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
  int	n_philo;
  int	philo_id;
  int	time_to_die;
  int	time_to_eat;
  int	time_to_sleep;
  int	n_time_to_eat;
  int	n_forks;
} t_philo;

int	ft_isdigit(int c);
int	ft_atoi(const char *nptr);
void free_exit(t_philo *philo);
#endif