#include "philo.h"

int isit_end(t_philo *phil)
{
	int res;

	if (pthread_mutex_lock(phil->sim->end_lock))
		return (sim_print(phil, ERROR, "mutex lock error"));
	res = 0;
	if (phil->sim->end)
		res = 1;
	if (pthread_mutex_unlock(phil->sim->end_lock))
		return (sim_print(phil, ERROR, "mutex unlock error"));
	return (res);
}

int sim_print(t_philo *phil, int flag, char *mes)
{
	if (pthread_mutex_lock(phil->sim->print_lock))
		return (error("mutex lock error", NULL));
	if (flag == ERROR)
		error(mes, NULL);
	else
	{
		if (pthread_mutex_lock(phil->sim->end_lock))
			return (error("mutex lock error", NULL));
		if (!phil->sim->end || (phil->sim->end && mes == DIED))
			printf("%lums %d %s", now() - phil->sim->start, phil->id, mes);
		if (pthread_mutex_unlock(phil->sim->end_lock))
			return (error("mutex unlock error", NULL));
	}
	if (pthread_mutex_unlock(phil->sim->print_lock))
		return (error("mutex unlock error", NULL));
	if (flag == ERROR)
		return (1);
	return (0);
}

static void *cycle(void *p)
{
	t_philo *phil;

	phil = (t_philo *)p;

}

void simulation(t_sim *sim)
{
	size_t i;

	i = 0;
	sim->start = now();
	while (i < sim->num)
	{
		sim->philos[i].last_eat = sim->start;
		if (pthread_create(sim->threads[i++], NULL, cycle, &sim->philos[i]))
			return (error("thread error", sim));
	}
	if (supervisor(sim))
		return ;
	i = 0;
	while (i < sim->num)
	{
		if (pthread_join(*sim->threads[i], NULL))
			return (error("thread error", NULL));
	}
}