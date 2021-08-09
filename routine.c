#include "philo.h"

int eat(t_philo *phil)
{
	if (pthread_mutex_lock(phil->lasteat_lock))
		return (sim_print(phil, ERROR, "mutex lock error"));
	printf("%zu blocks lasteat\n", phil->id);
	phil->last_eat = now();
	if (pthread_mutex_unlock(phil->lasteat_lock))
		return (sim_print(phil, ERROR, "mutex unlock error"));
	printf("%zu unblocks lasteat\n", phil->id);
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
	{
		printf("%zu takes left fork with id %d\n", phil->id, phil->left_fork->id);
		return (phil->left_fork);
	}
	printf("%zu takes right fork with id %d\n", phil->id, phil->right_fork->id);
	return (phil->right_fork);
}

int forks(t_philo *phil, t_fork *fork)
{
	int i;
	t_fork *curr_fork;

	i = 2;
	curr_fork = fork;
	while (i)
	{
		printf("%zu tries to block %d fork\n", phil->id, curr_fork->id);
		if (pthread_mutex_lock(curr_fork->fork_lock))
			return (sim_print(phil, ERROR, "mutex lock error"));
		printf("%zu blocks %d fork\n", phil->id, curr_fork->id);
		if (phil->id == curr_fork->last_user)
		{
			if (pthread_mutex_unlock(curr_fork->fork_lock))
				return (sim_print(phil, ERROR, "mutex unlock error"));
			printf("%zu unblocks fork, because already use\n", phil->id);
			continue;
		}
		curr_fork->last_user = phil->id;
		if (sim_print(phil, PHILO, FORK))
			return (1);
		if (--i)
		{
			if (phil->id % 2)
				curr_fork = phil->right_fork;
			else
				curr_fork = phil->left_fork;
		}
	}
	return (0);
}

int isit_end(t_philo *phil)
{
	int res;

	if (pthread_mutex_lock(phil->sim->end_lock))
		return (sim_print(phil, ERROR, "mutex lock error"));
	printf("%zu blocks end\n", phil->id);
	res = 0;
	if (phil->sim->end)
		res = 1;
	if (pthread_mutex_unlock(phil->sim->end_lock))
		return (sim_print(phil, ERROR, "mutex unlock error"));
	printf("%zu unblocks end\n", phil->id);
	return (res);
}

int sim_print(t_philo *phil, int flag, char *mes)
{
	if (pthread_mutex_lock(phil->sim->print_lock))
		return (error("mutex lock error", NULL));
	printf("%zu blocks print\n", phil->id);
	if (flag == ERROR)
		error(mes, NULL);
	else
	{
		if (pthread_mutex_lock(phil->sim->end_lock))
			return (error("mutex lock error", NULL));
		printf("%zu blocks end\n", phil->id);
		if (!phil->sim->end || (phil->sim->end && mes == DIED))
			printf("%zums %zu %s", now() - phil->sim->start, phil->id, mes);
		if (pthread_mutex_unlock(phil->sim->end_lock))
			return (error("mutex unlock error", NULL));
		printf("%zu unblocks end\n", phil->id);
	}
	if (pthread_mutex_unlock(phil->sim->print_lock))
		return (error("mutex unlock error", NULL));
	printf("%zu unblocks print\n", phil->id);
	if (flag == ERROR)
		return (1);
	return (0);
}