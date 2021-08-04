#include "philo.h"

static int	setup_utils(t_sim *sim)
{
	size_t i;

	i = 0;
	while (i < sim->num)
	{
		sim->forks[i].fork_lock = \
		(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!sim->forks[i].fork_lock)
			return (error("malloc error", sim));
		if (pthread_mutex_init(sim->forks[i].fork_lock, NULL))
			return (error("mutex error", sim));
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
	sim->forks = (t_fork *)malloc(sizeof(t_fork) * sim->num);
	sim->status_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	sim->threads = (pthread_t **)malloc(sizeof(pthread_t *) * sim->num);
	if (!sim->philos || !sim->forks || !sim->status_lock || !sim->threads)
		return (error("malloc error", sim));
	if (pthread_mutex_init(sim->status_lock, NULL))
		return (error("mutex error", sim));
	memset(sim->forks, 0, sizeof(t_fork) * sim->num);
	memset(sim->threads, 0, sizeof(pthread_t *) * sim->num);
	return (setup_utils(sim));
}