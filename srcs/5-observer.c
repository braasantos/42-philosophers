#include "../inc/philo.h"

void	*control_philos(void *arg)
{
 	t_data	*data;

 	data = (t_data *)arg;
	while(1)
	{
		if(check_dead(data) == 1)
		{
			clean(data);
			safe_pthread(&data->observer, NULL, NULL, DETACH);
		}
	}
 	return (NULL);
}

int	check_dead(t_data *data)
{
	size_t	time_since_last_meal;
	size_t	i;

	i = 0;
	while(i < data->n_philo)
	{
		time_since_last_meal = get_time() - data->philosopher[i].last_meal;
		if (time_since_last_meal >= data->philosopher[i].data->time_to_die)
		{
			ft_status(0, data->philosopher);
			return (1);
		}
		i++;
	}
	return (0);
}
