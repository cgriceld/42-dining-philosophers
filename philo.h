#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#define EINVAL 22
#define DIED "died\n"
#define FORK "has taken a fork\n"
#define EAT "is eating\n"
#define SLEEP "is sleeping\n"
#define THINK "is thinking\n"

typedef enum	e_print
{
	ERROR,
	PHILO
}				t_print;

typedef struct	s_fork
{
	pthread_mutex_t	*fork_lock;
	size_t			last_user;
}				t_fork;

typedef struct	s_philo
{
	size_t	id;
	size_t	already_eat;
	size_t	last_eat;
	pthread_mutex_t	*lasteat_lock;
	t_fork	*left_fork;
	t_fork	*right_fork;
	t_sim	*sim;
}				t_philo;

/*
** start - start time of simulation in ms
** end - flag to end simualtion
*/
typedef struct	s_sim
{
	size_t num;
	size_t to_die;
	size_t to_eat;
	size_t to_sleep;
	size_t total_meals;
	size_t start;
	t_philo *philos;
	t_fork *forks;
	pthread_t **threads;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*end_lock;
	int end;
}				t_sim;

int error(char *mes, t_sim *sim);
int setup(t_sim *sim);
void simulation(t_sim *sim);
int supervisor(t_sim *sim);
int sim_print(t_philo *phil, int flag, char *mes);
int isit_end(t_philo *phil);
t_fork *choose_fork(t_philo *phil);
int forks(t_philo *phil, t_fork *fork);
int eat(t_philo *phil);
int pwait(size_t to_do, size_t to_die);
int ft_atoi(size_t *target, char *arg);
size_t now(void);

#endif