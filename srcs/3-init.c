#include "../inc/philo.h"

void	data_init(t_data *data)
{
	size_t	i;

	i = 0;
	data->forks = safe_malloc(sizeof(t_fork) * data->n_philo);
	data->philosopher = safe_malloc(sizeof(t_philo) * data->n_philo);
	data->died = 0;
	safe_mutex(&data->write_mutex, INIT);
	while (i < data->n_philo)
	{
		safe_mutex(&data->forks[i].fork, INIT);
		data->forks[i].fork_id = i;
		i++;
	}
	init_philo(data);
}

void	init_philo(t_data *data)
{
	size_t	i;
	t_philo *philo;

	i = 0;
	while (i < data->n_philo)
	{
		philo = data->philosopher + i;
		philo->philo_id = i + 1;
		philo->dead = 0;
		philo->meals_count = 0;
		// safe_mutex(&philo[i].controller, INIT);
		philo->data = data;
		get_forks(philo, data->forks, i);
		i++;
	}
}

void	get_forks(t_philo *philo, t_fork *forks, int position)
{
	philo->l_fork = &forks[(position + 1) % philo->data->n_philo];
	philo->r_fork = &forks[position];
	if (philo->philo_id % 2 == 0)
	{
		philo->l_fork = &forks[position];
		philo->r_fork = &forks[(position + 1) % philo->data->n_philo];
	}
}
