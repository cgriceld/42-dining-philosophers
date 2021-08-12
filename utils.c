/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 11:49:43 by cgriceld          #+#    #+#             */
/*   Updated: 2021/08/12 11:49:44 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(size_t *target, char *arg)
{
	*target = 0;
	while (*arg >= '0' && *arg <= '9')
		*target = *target * 10 + (*arg++ - 48);
	if (*arg)
		return (1);
	return (0);
}

size_t	now(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((size_t)t.tv_sec * 1000 + (size_t)t.tv_usec / 1000);
}
