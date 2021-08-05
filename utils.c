#include "philo.h"

int		ft_atoi(size_t *target, char *arg)
{
	*target = 0;
	while (*arg >= '0' && *arg <= '9')
		*target = *target * 10 + (*arg++ - 48);
	if (*arg)
		return (1);
	return (0);
}

size_t	now(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((size_t)time.tv_usec / 1000 + (size_t)time.tv_sec * 1000);
}