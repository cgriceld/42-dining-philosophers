#include "philo.h"

static void	clean(t_sim *sim)
{
	size_t i;

	free(sim->philos);
	if (sim->status_lock && pthread_mutex_destroy(sim->status_lock) != EINVAL)
		error("mutex error", NULL);
	free(sim->status_lock);
	i = 0;
	while (i < sim->num)
	{
		if (sim->forks)
		{
			if (sim->forks[i].fork_lock && \
				pthread_mutex_destroy(sim->forks[i].fork_lock) != EINVAL)
				error("mutex error", NULL);
			free(sim->forks[i].fork_lock);
		}
		if (sim->threads)
			free(sim->threads[i]);
	}
	free(sim->forks);
	free(sim->threads);
}

int			error(char *mes, t_sim *sim)
{
	if (mes)
		printf("Error : %s\n", mes);
	if (sim)
		clean(sim);
	return (1);
}

static int	ft_atoi(size_t *target, char *arg)
{
	*target = 0;
	while (*arg >= '0' && *arg <= '9')
		*target = *target * 10 + (*arg++ - 48);
	if (*arg)
		return (1);
	return (0);
}

static int	parser(t_sim *sim, int argc, char **argv)
{
	if (argc != 5 || argc != 6)
		return (error("invalid argument", NULL));
	if (argc == 5)
		sim->total_meals = -1;
	if (ft_atoi(&sim->num, argv[1]) || sim->num < 2 || \
		ft_atoi(&sim->to_die, argv[2]) || ft_atoi(&sim->to_eat, argv[3]) || \
		ft_atoi(&sim->to_sleep, argv[4]) || \
		(argc == 6 && ft_atoi(&sim->total_meals, argv[5])))
		return (error("invalid argument", NULL));
	return (0);
}

int			main(int argc, char **argv)
{
	t_sim sim;

	if (parser(&sim, argc, argv))
		return (1);
	if (argc == 6 && !sim.total_meals)
		return (0);
	if (setup(&sim))
		return (1);
	error(NULL, &sim);
	return (0);
}