#include "philo.h"

static int mark_end(t_sim *sim, size_t id, int *res)
{
	if (pthread_mutex_lock(sim->end_lock))
		return (sim_print(&sim->philos[0], ERROR, "mutex lock error"));
	if (sim->philos[id].already_eat != sim->total_meals)
	{
		sim->end = 1;
		*res = 1;
	}
	if (pthread_mutex_unlock(sim->end_lock))
		return (sim_print(&sim->philos[0], ERROR, "mutex unlock error"));
	if (*res)
		return (sim_print(&sim->philos[id], PHILO, DIED));
	return (0);
}

int supervisor(t_sim *sim)
{
	size_t id;
	int res;

	id = 0;
	res = 0;
	while (1)
	{
		usleep(100);
		if (pthread_mutex_lock(sim->philos[id].lasteat_lock))
			return (sim_print(&sim->philos[0], ERROR, "mutex lock error"));
		if ((sim->to_die < now() - sim->philos[id].last_eat) && mark_end(sim, id, &res))
			return (1);
		if (pthread_mutex_unlock(sim->philos[id].lasteat_lock))
			return (sim_print(&sim->philos[0], ERROR, "mutex unlock error"));
		if (res)
			return (0);
		if (++id == sim->num)
			id = 0;
	}
}