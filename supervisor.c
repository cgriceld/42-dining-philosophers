#include "philo.h"

static int	report_dead(t_philo *phil)
{
	if (pthread_mutex_lock(phil->sim->print_lock))
		return (error("mutex lock error", NULL));
	printf("%zu %zu died\n", now() - phil->sim->start, phil->id);
	return (pthread_mutex_unlock(phil->sim->print_lock) ? \
		error("mutex unlock error", NULL) : 0);
}

static int	check_health(t_sim *sim, size_t id, int *susp, int *print)
{
	if (pthread_mutex_lock(sim->end_lock))
		return (sim_print(&sim->philos[0], ERROR, "mutex lock error"));
	if (!sim->in_process)
		*susp = 0;
	*print = 0;
	if (sim->philos[id].alive)
	{
		*print = 1;
		sim->end = 1;
	}
	if (pthread_mutex_unlock(sim->end_lock))
		return (sim_print(&sim->philos[0], ERROR, "mutex unlock error"));
	if ((!*susp || *print) && \
		pthread_mutex_unlock(sim->philos[id].lasteat_lock))
		return (sim_print(&sim->philos[0], ERROR, "mutex unlock error"));
	return (*print ? report_dead(&sim->philos[id]) : 0);
}


int	supervisor(t_sim *sim)
{
	size_t	id;
	int		susp;
	int		print;

	id = 0;
	while (1)
	{
		usleep(100);
		if (pthread_mutex_lock(sim->philos[id].lasteat_lock))
			return (sim_print(&sim->philos[0], ERROR, "mutex lock error"));
		susp = 0;
		if (sim->to_die < now() - sim->philos[id].last_eat)
			susp = 1;
		if (susp)
		{
			if (check_health(sim, id, &susp, &print))
				return (1);
			if (!susp || print)
				return (0);
		}
		if (pthread_mutex_unlock(sim->philos[id].lasteat_lock))
			return (sim_print(&sim->philos[0], ERROR, "mutex unlock error"));
		id = (id + 1) % sim->num;
	}
}
