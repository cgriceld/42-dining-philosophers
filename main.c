#include "philo.h"

static int	parser(t_sim *sim, int argc, char **argv)
{
	size_t total;

	if (argc < 5 || argc > 6)
		return (error("invalid argument", NULL));
	if (argc == 5)
		sim->total_meals = -1;
	if (ft_atoi(&sim->num, argv[1]) || !sim->num || \
		ft_atoi(&sim->to_die, argv[2]) || ft_atoi(&sim->to_eat, argv[3]) || \
		ft_atoi(&sim->to_sleep, argv[4]))
		return (error("invalid argument", NULL));
	if (argc == 6)
	{
		total = (size_t)sim->total_meals;
		if (ft_atoi(&total, argv[5]))
			return (error("invalid argument", NULL));
		sim->total_meals = total;
	}
	return (0);
}

int			main(int argc, char **argv)
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
			printf("wait for %zu\n", i);
			if (pthread_join(*sim.threads[i], NULL) && \
				error("thread error", NULL))
				break ;
			i++;
		}
	}
	printf("join all\n");
	error(NULL, &sim);
	return (0);
}