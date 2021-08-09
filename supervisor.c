#include "philo.h"

// static int	mark_end(t_sim *sim, size_t id, int *res)
// {
// 	if (pthread_mutex_lock(sim->end_lock))
// 		return (sim_print(&sim->philos[0], ERROR, "mutex lock error"));
// 	sim->end = 1;
// 	if (pthread_mutex_unlock(sim->end_lock))
// 		return (sim_print(&sim->philos[0], ERROR, "mutex unlock error"));
// 	*res = 1;
// 	if (sim->philos[id].already_eat != sim->total_meals)
// 		return (sim_print(&sim->philos[id], PHILO, DIED));
// 	return (0);
// }

// 1 - error
int			supervisor(t_sim *sim)
{
	size_t id;
	int susp;
	int print;

	id = 0;
	susp = 0;
	print = 0;
	while (1)
	{
		usleep(100);
		if (pthread_mutex_lock(sim->philos[id].lasteat_lock))
			return (sim_print(&sim->philos[0], ERROR, "mutex lock error"));
		if (sim->to_die < now() - sim->philos[id].last_eat)
			susp = 1;
		if (pthread_mutex_unlock(sim->philos[id].lasteat_lock))
			return (sim_print(&sim->philos[0], ERROR, "mutex unlock error"));
		if (susp)
		{
			if (pthread_mutex_lock(sim->end_lock))
				return (sim_print(&sim->philos[0], ERROR, "mutex lock error"));
			if (!sim->in_process) // return 0
				susp = 0;
			if (sim->philos[id].alive)
			{
				print = 1;
				sim->end = 1;
			}
			if (pthread_mutex_unlock(sim->end_lock))
				return (sim_print(&sim->philos[0], ERROR, "mutex unlock error"));
			if (print)
				return (sim_print(&sim->philos[id], PHILO, DIED));
			if (!susp)
				return (0);
		}
		if (++id == sim->num)
			id = 0;
	}
}