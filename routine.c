#include "philo.h"

int eat(t_philo *phil)
{
	if (pthread_mutex_lock(phil->lasteat_lock))
		return (sim_print(phil, ERROR, "mutex lock error"));
	phil->last_eat = now();
	if (pthread_mutex_unlock(phil->lasteat_lock))
		return (sim_print(phil, ERROR, "mutex unlock error"));
	if (sim_print(phil, PHILO, EAT))
		return (1);
	phil->already_eat++;
	if (pwait(phil->sim->to_eat, phil->sim->to_die))
		return (1);
	return (0);
}

t_fork *choose_fork(t_philo *phil)
{
	if (phil->id % 2)
		return (phil->left_fork);
	return (phil->right_fork);
}

int forks(t_philo *phil, t_fork *fork)
{
	int i;
	t_fork *curr_fork;

	i = 3;
	curr_fork = fork;
	while (--i)
	{
		if (pthread_mutex_lock(curr_fork->fork_lock))
			return (sim_print(phil, ERROR, "mutex lock error"));
		if (phil->id == curr_fork->last_user)
		{
			if (pthread_mutex_unlock(curr_fork->fork_lock))
				return (sim_print(phil, ERROR, "mutex unlock error"));
			continue;
		}
		curr_fork->last_user = phil->id;
		if (sim_print(phil, PHILO, FORK))
			return (1);
		if (phil->id % 2)
			curr_fork = phil->right_fork;
		else
			curr_fork = phil->left_fork;
	}
	return (0);
}

int isit_end(t_philo *phil)
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