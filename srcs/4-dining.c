#include "../inc/philo.h"

void	create_thread(t_data *data)
{
	size_t			i;

	i = -1;
	while (++i < data->n_philo)
		safe_pthread(&data->philosopher[i].thread, &philo, &data->philosopher[i], CREATE);
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
		usleep(2000);
	while(philosopher->data->died == 0)
	{
		if (grab_forks(philosopher) == 1)
			return (NULL);
		if (ft_eat(philosopher) == 1)
			return (NULL);
		if (ft_sleeping(philosopher) == 1)
			return (NULL);
		if (ft_thinking(philosopher) == 1)
			return (NULL);
	}
	return (NULL);
}
int	ft_sleeping(t_philo *philo)
{
	safe_mutex(&philo->data->mutex, LOCK);
	if (philo->data->died >= 1 || philo->data->all_ate == philo->data->n_philo)
	{
		safe_mutex(&philo->data->mutex, UNLOCK);
		return (1);
	}
	safe_mutex(&philo->data->mutex, UNLOCK);
	ft_status(5, philo);
	ft_usleep(philo->data->time_to_sleep);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	safe_mutex(&philo->data->mutex, LOCK);
	if (philo->data->died >= 1 || philo->data->all_ate == philo->data->n_philo)
	{
		safe_mutex(&philo->data->mutex, UNLOCK);
		safe_mutex(&philo->l_fork->fork, UNLOCK);
		safe_mutex(&philo->r_fork->fork, UNLOCK);
		return (1);
	}
	safe_mutex(&philo->data->mutex, UNLOCK);
	safe_mutex(&philo->philo_mutex, LOCK);
	philo->last_meal = get_time();
	ft_status(3, philo);
	safe_mutex(&philo->data->mutex, LOCK);
	philo->meals_count += 1;
	if (philo->data->n_time_to_eat != philo->data->j)
	{
		if (philo->meals_count == philo->data->n_time_to_eat)
			philo->data->all_ate += 1;
	}
	safe_mutex(&philo->data->mutex, UNLOCK);
	safe_mutex(&philo->philo_mutex, UNLOCK);
	ft_usleep(philo->data->time_to_eat);
	safe_mutex(&philo->l_fork->fork, UNLOCK);
	safe_mutex(&philo->r_fork->fork, UNLOCK);
	return (0);
}

int	ft_thinking(t_philo *philo)
{
	safe_mutex(&philo->data->mutex, LOCK);
	if (philo->data->died >= 1 || philo->data->all_ate == philo->data->n_philo)
	{
		safe_mutex(&philo->data->mutex, UNLOCK);
		return (1);
	}
	safe_mutex(&philo->data->mutex, UNLOCK);
	ft_status(4, philo);
	return (0);
}
