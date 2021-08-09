#include "philo.h"

int			sim_print(t_philo *phil, int flag, char *mes)
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
			printf("%zums %zu %s", now() - phil->sim->start, phil->id, mes);
		if (pthread_mutex_unlock(phil->sim->end_lock))
			return (error("mutex unlock error", NULL));
	}
	if (pthread_mutex_unlock(phil->sim->print_lock))
		return (error("mutex unlock error", NULL));
	if (flag == ERROR)
		return (1);
	return (0);
}

static int	isit_end(t_philo *phil)
{
	int flag;

	if (pthread_mutex_lock(phil->sim->end_lock))
		return (sim_print(phil, ERROR, "mutex lock error"));
	flag = 0;
	if (phil->sim->end)
		flag++;
	if (pthread_mutex_unlock(phil->sim->end_lock))
		return (sim_print(phil, ERROR, "mutex unlock error"));
	return (flag);
}

int			pwait(size_t to_do, size_t to_die)
{
	size_t begin;
	size_t curr;

	begin = now();
	curr = begin;
	while (curr - begin < to_do)
	{
		usleep(100);
		curr = now();
		if (curr - begin > to_die)
			return (1);
	}
	return (0);
}

static void	*cycle(void *p)
{
	t_philo	*phil;
	int		res;

	phil = (t_philo *)p;
	while (1)
	{
		if (isit_end(phil) || forks(phil, choose_fork(phil)))
			return (NULL);
		res = isit_end(phil);
		if (!res && eat(phil))
			res = 1;
		if (pthread_mutex_unlock(phil->right_fork->fork_lock) || \
			pthread_mutex_unlock(phil->left_fork->fork_lock))
		{
			sim_print(phil, ERROR, "mutex unlock error");
			res = 1;
		}
		if (res)
			return (NULL);
		if (isit_end(phil) || sim_print(phil, PHILO, SLEEP) || \
			pwait(phil->sim->to_sleep, phil->sim->to_die) || \
			isit_end(phil) || sim_print(phil, PHILO, THINK))
			return (NULL);
	}
	return (NULL);
}

int			simulation(t_sim *sim)
{
	size_t i;

	i = 0;
	sim->start = now();
	while (i < sim->num)
	{
		sim->philos[i].last_eat = sim->start;
		if (pthread_create(sim->threads[i], NULL, cycle, &sim->philos[i]) && \
			error("thread error", NULL))
			return (0);
		i++;
	}
	if (supervisor(sim))
		return (0);
	return (1);
}