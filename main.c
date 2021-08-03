#include "philo.h"

int error(char *mes, t_sim *sim)
{
	printf("Error : %s\n", mes);
	if (sim)
	{
		free(sim->philos);
		free(sim->forks);
	}
	return (1);
}

static int ft_atoi(size_t *target, char *arg)
{
	*target = 0;
	while (*arg >= '0' && *arg <= '9')
		*target = *target * 10 + (*arg++ - 48);
	if (*arg)
		return (1);
	return (0);
}

static int parser(t_sim *sim, int argc, char **argv)
{
	if (argc != 5 || argc != 6)
		return (error("invalid argument", NULL));
	if (argc == 5)
		sim->total_meals = -1;
	if (ft_atoi(&sim->num, argv[1]) || sim->num < 2 || sim->num > 200 || \
		ft_atoi(&sim->to_die, argv[2]) || sim->to_die < 60 || ft_atoi(&sim->to_eat, argv[3]) || \
		sim->to_eat < 60 || ft_atoi(&sim->to_sleep, argv[4]) || sim->to_sleep < 60 || \
		(argc == 6 && ft_atoi(&sim->total_meals, argv[5])))
		return (error("invalid argument", NULL));
	return (0);
}

int main(int argc, char **argv)
{
	t_sim sim;

	if (!parser(&sim, argc, argv))
	{
		if (argc == 6 && !sim.total_meals)
			return (0);
		setup(&sim);
	}
	return (0);
}