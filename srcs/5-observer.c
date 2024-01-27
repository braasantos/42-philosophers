#include "../inc/philo.h"

void	*control_philos(void *arg)
{
 	t_data	*data;

 	data = (t_data *)arg;
	while(1)
		if(check_dead(data) == 1 || check_n_meals(data) == 1)
			return (NULL);
 	return (NULL);
}

int	check_dead(t_data *data)
{
	size_t	curr_time;
	size_t	i;

	i = 0;
	while(i < data->n_philo)
	{
		safe_mutex(&data->philosopher[i].philo_mutex, LOCK);
		curr_time = get_time() - data->philosopher[i].last_meal;
		if (curr_time >= data->philosopher[i].data->time_to_die)
		{
			ft_status(0, data->philosopher);
			safe_mutex(&data->death_mutex, LOCK);
			data->died = 1;
			safe_mutex(&data->death_mutex, UNLOCK);
			safe_mutex(&data->philosopher[i].philo_mutex, UNLOCK);
			return (1);
		}
		safe_mutex(&data->philosopher[i].philo_mutex, UNLOCK);
		i++;
	}
	return (0);
}
int	check_n_meals(t_data *data)
{
	size_t	j;

	j = -1;
	if (data->n_time_to_eat == j)
		return (0);
	safe_mutex(&data->death_mutex, LOCK);
	if (data->all_ate == data->n_philo)
	{
		safe_mutex(&data->death_mutex, UNLOCK);
		return (1);
	}
	safe_mutex(&data->death_mutex, UNLOCK);
	return (0);
}

int	grab_forks(t_philo *philo)
{
	safe_mutex(&philo->data->mutex, LOCK);
	if (philo->data->died >= 1 || philo->data->all_ate == philo->data->n_philo)
	{
		safe_mutex(&philo->data->mutex, UNLOCK);
		return (1);
	}
	safe_mutex(&philo->data->mutex, UNLOCK);
	if (philo->philo_id % 2 == 0)
	{
	safe_mutex(&philo->r_fork->fork, LOCK);
	ft_status(1, philo);
	safe_mutex(&philo->l_fork->fork, LOCK);
	ft_status(1, philo);
	}
	else
	{
		safe_mutex(&philo->l_fork->fork, LOCK);
		ft_status(1, philo);
		safe_mutex(&philo->r_fork->fork, LOCK);
		ft_status(1, philo);
	}
	return (0);
}
void	join_threads(t_data *data)
{
	size_t	i;

	i = 0;
	safe_pthread(&data->observer,NULL, NULL, JOIN);
	while (i < data->n_philo)
	{
		safe_pthread(&data->philosopher[i].thread, NULL, NULL, JOIN);
		usleep(1000);
		i++;
	}
}