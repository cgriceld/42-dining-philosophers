#include "philo.h"

static void	clean_mtx(pthread_mutex_t *mtx)
{
	int	res;

	if (mtx)
	{
		res = pthread_mutex_destroy(mtx);
		if (res && res != EINVAL)
			error("mutex error", NULL);
	}
	free(mtx);
}

static void	clean(t_sim *sim)
{
	size_t	i;

	clean_mtx(sim->print_lock);
	clean_mtx(sim->end_lock);
	i = 0;
	while (i < sim->num)
	{
		if (sim->philos)
			clean_mtx(sim->philos[i].lasteat_lock);
		if (sim->forks)
			clean_mtx(sim->forks[i].fork_lock);
		if (sim->threads)
			free(sim->threads[i]);
		i++;
	}
	free(sim->philos);
	free(sim->forks);
	free(sim->threads);
}

int	error(char *mes, t_sim *sim)
{
	if (mes)
		printf("Error : %s\n", mes);
	if (sim)
		clean(sim);
	return (1);
}
