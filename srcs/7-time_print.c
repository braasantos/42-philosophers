#include "../inc/philo.h"

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		printf("gettimeofday() error\n");
	return (time.tv_sec * 1e3 + time.tv_usec / 1e3); // 1000
}

size_t	ft_usleep(size_t time)
{
	size_t	start;
	
	start = get_time();
	while ((get_time() - start) < time)
		usleep(time * 1e3);
	return (0);
}

void	ft_status(int n, t_philo *philo)
{
	size_t	curr_time;

	safe_mutex(&philo->data->write_mutex, LOCK);
	curr_time = get_time() - philo->data->starting_time;
	if (n == 1 || n == 2)
		printf("%zu %d has taken a fork\n", curr_time, philo->philo_id);
	else if (n == 3)
		printf("%zu %d is eating\n",curr_time, philo->philo_id);
	else if (n == 4)
		printf("%zu %d is thinking\n",curr_time, philo->philo_id);
	else if (n == 5)
		printf("%zu %d is sleeping\n",curr_time, philo->philo_id);
	else if (n == 0)
		printf("%zu %d died\n",curr_time, philo->philo_id);
	safe_mutex(&philo->data->write_mutex, UNLOCK);
}
