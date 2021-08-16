#include "philo.h"

static int	parser(t_sim *sim, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (error("invalid argument", NULL));
	if (argc == 5)
		sim->total_meals = -1;
	return ((ft_atoi(&sim->num, argv[1]) || !sim->num || \
		ft_atoi(&sim->to_die, argv[2]) || ft_atoi(&sim->to_eat, argv[3]) || \
		ft_atoi(&sim->to_sleep, argv[4]) || \
		(argc == 6 && ft_atoi(&sim->total_meals, argv[5]))) ? \
		error("invalid argument", NULL) : 0);
}

int	main(int argc, char **argv)
{
	t_sim	sim;
	size_t	i;

	memset(&sim, 0, sizeof(t_sim));
	if (parser(&sim, argc, argv))
		return (1);
	if (argc == 6 && !sim.total_meals)
		return (0);
	if (setup(&sim))
		return (1);
	if (simulation(&sim))
	{
		i = 0;
		while (i < sim.num)
		{
			if (pthread_join(*sim.threads[i], NULL) && \
				error("thread error", NULL))
				break ;
			i++;
		}
	}
	error(NULL, &sim);
	return (0);
}
