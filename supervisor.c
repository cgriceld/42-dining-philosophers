/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 11:49:04 by cgriceld          #+#    #+#             */
/*   Updated: 2021/08/12 11:49:06 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (*print)
		return (sim_print(&sim->philos[id], PHILO, DIED));
	return (0);
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
		if (pthread_mutex_unlock(sim->philos[id].lasteat_lock))
			return (sim_print(&sim->philos[0], ERROR, "mutex unlock error"));
		if (susp)
		{
			if (check_health(sim, id, &susp, &print))
				return (1);
			if (!susp || print)
				return (0);
		}
		if (++id == sim->num)
			id = 0;
	}
}
