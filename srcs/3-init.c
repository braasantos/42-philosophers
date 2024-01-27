#include "../inc/philo.h"

void	data_init(t_data *data)
{
	size_t	i;

	i = 0;
	data->forks = safe_malloc(sizeof(t_fork) * data->n_philo);
	data->philosopher = safe_malloc(sizeof(t_philo) * data->n_philo);
	data->died = 0;
	data->full = 0;
	data->all_ate = 0;
	data->j = -1;
	data->starting_time = get_time();
	safe_mutex(&data->write_mutex, INIT);
	safe_mutex(&data->death_mutex, INIT);
	safe_mutex(&data->mutex, INIT);
	while (i < data->n_philo)
	{
		data->philosopher[i].last_meal = get_time();
		safe_mutex(&data->forks[i].fork, INIT);
		safe_mutex(&data->philosopher[i].philo_mutex, INIT);
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
