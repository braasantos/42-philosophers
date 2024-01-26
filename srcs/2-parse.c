#include "../inc/philo.h"

void	check_args(char **av, t_data  *data)
{
	if (ft_atol(av[1])== 18 || ft_atol(av[1])== 0)
		print_error(1);
	if (ft_atol(av[2])== 18 || ft_atol(av[2])== 0)
		print_error(2);
	if (ft_atol(av[3])== 18 || ft_atol(av[3])== 0)
		print_error(3);
	if (ft_atol(av[4])== 18 || ft_atol(av[4])== 0)
		print_error(4);
	if (av[5])
	{
		if (ft_atol(av[5])== 18 || ft_atol(av[5])== 0)
			print_error(5);
	}
	parse_args(data, av);
	return ;
}

void	parse_args(t_data *data, char **av)
{
	data->n_philo = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		data->n_time_to_eat = ft_atol(av[5]);
	else
		data->n_time_to_eat = -1;
	return ;
}
