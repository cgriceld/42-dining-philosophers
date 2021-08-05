#include "philo.h"

static int	setup_mtx(pthread_mutex_t *mtx, t_sim *sim)
{
	mtx = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!mtx)
		return (error("malloc error", sim));
	if (pthread_mutex_init(mtx, NULL))
		return (error("mutex error", sim));
	return (0);
}

static int	setup_sim(t_sim *sim)
{
	size_t i;

	i = 0;
	while (i < sim->num)
	{
		if (setup_mtx(sim->forks[i].fork_lock, sim))
			return (1);
		if (setup_mtx(sim->philos[i].lasteat_lock, sim))
			return (1);
		sim->philos[i].id = i + 1;
		sim->philos[i].left_fork = &sim->forks[i];
		sim->philos[i].right_fork = &sim->forks[(i + 1) % sim->num];
		sim->philos[i++].already_eat = 0;
		sim->threads[i] = (pthread_t *)malloc(sizeof(pthread_t));
		if (!sim->threads[i])
			return (error("malloc error", sim));
	}
	return (0);
}

int			setup(t_sim *sim)
{
	sim->philos = (t_philo *)malloc(sizeof(t_philo) * sim->num);
	if (!sim->philos)
		return (error("malloc error", sim));
	memset(sim->philos, 0, sizeof(t_fork) * sim->num);
	sim->forks = (t_fork *)malloc(sizeof(t_fork) * sim->num);
	if (!sim->forks)
		return (error("malloc error", sim));
	memset(sim->forks, 0, sizeof(t_fork) * sim->num);
	sim->threads = (pthread_t **)malloc(sizeof(pthread_t *) * sim->num);
	if (!sim->threads)
		return (error("malloc error", sim));
	memset(sim->threads, 0, sizeof(pthread_t *) * sim->num);
	return (setup_mtx(sim->print_lock, sim) || setup_mtx(sim->end_lock, sim) \
			|| setup_sim(sim));
}