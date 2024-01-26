#include "../inc/philo.h"

void	create_thread(t_data *data)
{
	size_t			i;

	i = -1;
	data->starting_time = get_time();
	while (++i < data->n_philo)
	{
		safe_pthread(&data->philosopher[i].thread, 
			&philo, &data->philosopher[i], CREATE);
		usleep(1000);
	}
	safe_pthread(&data->observer, &control_philos, data, CREATE);
}

void	*philo(void *arg)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)arg;
	if (philosopher->data->n_philo == 1)
	{
		safe_mutex(&philosopher->l_fork->fork, LOCK);
		ft_status(1, philosopher);
		safe_mutex(&philosopher->l_fork->fork, UNLOCK);
		return (NULL);
	}
	if (philosopher->philo_id % 2 == 0)
		ft_usleep(2);
	while(philosopher->data->died == 0)
	{
		ft_eat(philosopher);
		ft_status(5, philosopher);
		ft_usleep(philosopher->data->time_to_sleep);
		ft_thinking(philosopher);
	}
	return (NULL);
}

void	ft_eat(t_philo *philo)
{

	// if (philo->philo_id % 2 == 0)
	// {
	// 	safe_mutex(&philo->r_fork->fork, LOCK);
	// 	ft_status(1, philo);
	// 	safe_mutex(&philo->l_fork->fork, LOCK);
	// 	ft_usleep(philo->data->time_to_eat);
	// 	philo->last_meal = get_time();
	// 	safe_mutex(&philo->l_fork->fork, UNLOCK);
	// 	safe_mutex(&philo->r_fork->fork, UNLOCK);
	// }
	// else
	// {
		safe_mutex(&philo->l_fork->fork, LOCK);
		ft_status(1, philo);
		safe_mutex(&philo->r_fork->fork, LOCK);
		ft_status(2, philo);
		ft_status(3, philo);
		ft_usleep(philo->data->time_to_eat);
		philo->last_meal = get_time();
		safe_mutex(&philo->l_fork->fork, UNLOCK);
		safe_mutex(&philo->r_fork->fork, UNLOCK);
	// }
}

void	ft_thinking(t_philo *philo)
{
	ft_status(4, philo);
}

void	join_threads(t_data *data)
{
	size_t	i;

	i = 0;
	safe_pthread(&data->observer,NULL, NULL, JOIN);
	while (i < data->n_philo)
	{
		safe_pthread(&data->philosopher[i].thread, NULL, NULL, JOIN);
		usleep(100);
		i++;
	}
}
