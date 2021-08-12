/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 11:47:44 by cgriceld          #+#    #+#             */
/*   Updated: 2021/08/12 11:47:46 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sim_print(t_philo *phil, int flag, char *mes)
{
	if (pthread_mutex_lock(phil->sim->print_lock))
		return (error("mutex lock error", NULL));
	if (flag == ERROR)
		error(mes, NULL);
	else
	{
		if (pthread_mutex_lock(phil->sim->end_lock))
			return (error("mutex lock error", NULL));
		if (!phil->sim->end)
			printf("%zu %zu %s", now() - phil->sim->start, phil->id, mes);
		if (pthread_mutex_unlock(phil->sim->end_lock))
			return (error("mutex unlock error", NULL));
	}
	if (pthread_mutex_unlock(phil->sim->print_lock))
		return (error("mutex unlock error", NULL));
	if (flag == ERROR)
		return (1);
	return (0);
}

static int	isit_end(t_philo *phil, int after_eat)
{
	int	flag;

	if (pthread_mutex_lock(phil->sim->end_lock))
		return (sim_print(phil, ERROR, "mutex lock error"));
	flag = 0;
	if (phil->sim->end)
		flag = 1;
	if (!flag && after_eat && (++phil->already_eat == phil->sim->total_meals))
	{
		flag = 1;
		phil->sim->in_process--;
		phil->alive = 0;
	}
	if (pthread_mutex_unlock(phil->sim->end_lock))
		return (sim_print(phil, ERROR, "mutex unlock error"));
	return (flag);
}

int	pwait(size_t to_do, size_t to_die)
{
	size_t	end;
	size_t	curr;
	size_t	begin;

	end = now() + to_do;
	curr = now();
	begin = curr;
	while (curr < end)
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
		if (isit_end(phil, 0) || forks(phil, choose_fork(phil)))
			return (NULL);
		res = isit_end(phil, 0);
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
		if (isit_end(phil, 1) || sim_print(phil, PHILO, SLEEP) || \
			pwait(phil->sim->to_sleep, phil->sim->to_die) || \
			isit_end(phil, 0) || sim_print(phil, PHILO, THINK))
			return (NULL);
	}
}

int	simulation(t_sim *sim)
{
	size_t	i;

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
