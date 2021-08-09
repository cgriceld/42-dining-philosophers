#include "philo.h"

int pwait(size_t to_do, size_t to_die)
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

void *cycle(void *p)
{
	t_philo *phil;
	int res;

	phil = (t_philo *)p;
	while (phil->already_eat != phil->sim->total_meals)
	{
		if (isit_end(phil) || forks(phil, choose_fork(phil)))
			break;
		res = isit_end(phil);
		if (!res && eat(phil))
			res = 1;
		if (pthread_mutex_unlock(phil->right_fork->fork_lock))
			sim_print(phil, ERROR, "mutex unlock error");
		printf("%zu unblocks %d fork\n", phil->id, phil->right_fork->id);
		if (pthread_mutex_unlock(phil->left_fork->fork_lock))
			sim_print(phil, ERROR, "mutex unlock error");
		printf("%zu unblocks %d fork\n", phil->id, phil->left_fork->id);
		if (res)
		{
			printf("%zu exit because death pf smb\n", phil->id);
			break;
		}
		if (isit_end(phil) || sim_print(phil, PHILO, SLEEP) || \
			pwait(phil->sim->to_sleep, phil->sim->to_die) || \
			isit_end(phil) || sim_print(phil, PHILO, THINK))
			break;
	}
	printf("%zu returned!!!\n", phil->id);
	return (NULL);
}

void simulation(t_sim *sim)
{
	size_t i;

	i = 0;
	sim->start = now();
	while (i < sim->num)
	{
		sim->philos[i].last_eat = sim->start;
		if (pthread_create(sim->threads[i], NULL, cycle, &sim->philos[i]))
		{
			error("thread error", NULL);
			return ;
		}
		i++;
	}
	if (supervisor(sim))
	{
		printf("get out of this shit\n");
		return ;
	}
	printf("get out of this shit\n");
	//return;
	i = 0;
	while (i < sim->num)
	{
		printf("wait for %zu\n", i);
		if (pthread_join(*sim->threads[i], NULL))
		{
			error("thread error", NULL);
			return ;
		}
		i++;
	}
	printf("JOIN ALL\n");
}