#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
int	ft_atoi(const char *nptr)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (nptr[i])
	{
		if (!ft_isdigit(nptr[i]))
			return (18);
		num = num * 10 + nptr[i] - 48;
		i++;
	}
	return (num);
}
