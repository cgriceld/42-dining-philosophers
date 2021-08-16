#include "philo.h"

int	eat(t_philo *phil)
{
	if (pthread_mutex_lock(phil->lasteat_lock))
		return (sim_print(phil, ERROR, "mutex lock error"));
	phil->last_eat = now();
	if (pthread_mutex_unlock(phil->lasteat_lock))
		return (sim_print(phil, ERROR, "mutex unlock error"));
	return ((sim_print(phil, PHILO, EAT) || \
			pwait(phil->sim->to_eat, phil->sim->to_die)) ? 1 : 0);
}

t_fork	*choose_fork(t_philo *phil)
{
	return (phil->id % 2 ? phil->left_fork : phil->right_fork);
}

static int	throw_fork(t_philo *phil, t_fork *curr_fork)
{
	if (pthread_mutex_unlock(curr_fork->fork_lock))
		return (sim_print(phil, ERROR, "mutex unlock error"));
	return (phil->sim->num == 1 ? 1 : 0);
}

int	forks(t_philo *phil, t_fork *fork)
{
	int		i;
	t_fork	*curr_fork;

	i = 3;
	curr_fork = fork;
	while (--i)
	{
		if (pthread_mutex_lock(curr_fork->fork_lock))
			return (sim_print(phil, ERROR, "mutex lock error"));
		if (phil->id == curr_fork->last_user)
		{
			if (throw_fork(phil, curr_fork))
				return (1);
			continue ;
		}
		curr_fork->last_user = phil->id;
		if (sim_print(phil, PHILO, FORK) || \
		(phil->sim->num == 1 && throw_fork(phil, curr_fork)))
			return (1);
		curr_fork = phil->id % 2 ? phil->right_fork : phil->left_fork;
	}
	return (0);
}
