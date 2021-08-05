#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define EINVAL 22

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
}				t_philo;

typedef struct	s_sim
{
	size_t num;
	size_t to_die;
	size_t to_eat;
	size_t to_sleep;
	size_t total_meals;
	t_philo *philos;
	t_fork *forks;
	pthread_t **threads;
	pthread_mutex_t	*print_lock;
	int end;
	pthread_mutex_t	*end_lock;
}				t_sim;

int error(char *mes, t_sim *sim);
int setup(t_sim *sim);

#endif