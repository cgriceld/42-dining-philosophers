#include "philo.h"

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

	memset(&sim, 0, sizeof(t_sim));
	if (parser(&sim, argc, argv))
		return (1);
	if (argc == 6 && !sim.total_meals)
		return (0);
	if (setup(&sim))
		return (1);
	simulation(&sim);
	error(NULL, &sim);
	return (0);
}