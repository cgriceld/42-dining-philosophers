#include "philo.h"

static int setup_threads(t_sim *sim)
{
	
}

static int setup_locks(t_sim *sim)
{
	if (pthread_mutex_init(sim->status_lock, NULL))
		return (1);
	// for forks
	return (0);
}

int setup(t_sim *sim)
{
	size_t i;

	sim->philos = (t_philo *)malloc(sizeof(t_philo) * sim->num);
	sim->forks = (t_fork *)malloc(sizeof(t_fork) * sim->num);
	sim->status_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!sim->philos || !sim->forks || !sim->status_lock)
		return (error("malloc error", sim));
	memset(sim->philos, 0, sizeof(t_philo) * sim->num);
	memset(sim->forks, 0, sizeof(t_fork) * sim->num);
	i = 0;
	while (i < sim->num)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].left_fork = &sim->forks[i];
		sim->philos[i].right_fork = &sim->forks[(i + 1) % sim->num];
		sim->philos[i++].already_eat = 0;
	}
	if (setup_locks(sim))
		return (error("mutex error", sim));
	if (setup_threads(sim))
		return (error("thread error", sim));
	return (0);
}