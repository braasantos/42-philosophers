#include "../inc/philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

long	ft_atol(const char *nptr)
{
	long	num;

	num = 0;
	while (*nptr)
	{
		if (!ft_isdigit(*nptr))
			return (18);
		num = num * 10 + *nptr - 48;
		nptr++;
	}
	if ((num  > 2147483647) || (num  < -2147483648))
		return (18);
	return (num);
}

void	*safe_malloc(size_t bytes)
{
	void	*mlc;
	mlc = malloc(bytes);
	if (mlc == NULL)
		printf("Error with malloc\n");
	return(mlc);
}

void	safe_mutex(pthread_mutex_t *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
	{
		if (pthread_mutex_lock(mutex) != 0)
			print_error(6);
	}
	else if (opcode == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex) != 0)
			print_error(6);
	}
	else if (opcode == INIT)
	{
		if (pthread_mutex_init(mutex, NULL) != 0)
			print_error(6);
	}
	else if (opcode == DESTROY)
	{
		pthread_mutex_destroy(mutex);
	}
	else
		print_error(6);
}

void	safe_pthread(pthread_t *thread, void *(*args)(void *),
		void *data, t_opcode opcode)
{
	if (opcode == CREATE)
	{
		if(pthread_create(thread, NULL, args, data) != 0)
			print_error(6);
	}
	else if (opcode == JOIN)
	{
		if (pthread_join(*thread, NULL) != 0)
			print_error(6);
	}
	else if (opcode == DETACH)
	{
		if (pthread_detach(*thread) != 0)
			print_error(6);
	}
	else
		print_error(6);
}
