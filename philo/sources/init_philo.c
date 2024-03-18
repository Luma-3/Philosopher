/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:50:52 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/18 23:12:31 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TODO destroy mutex

static int	init_fork_mutex(pthread_mutex_t *forks, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != SUCCESS)
			return (errno);
		i++;
	}
	return (SUCCESS);
}

// TODO free .thread amd .start_time_strave

static int	take_philo_arg(t_philo *philos, pthread_mutex_t *forks, t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->nb_philo)
	{
		philos[i].thread = malloc(sizeof(pthread_t));
		philos[i].strave_time = malloc(sizeof(struct timeval));
		philos[i].start_time = malloc(sizeof(struct timeval));
		if (!(philos[i].thread) || !(philos[i].strave_time)
			|| !(philos[i].start_time))
			return (ENOMEM);
		philos[i].id = i;
		philos[i].time_to_eat = arg->time_to_eat;
		philos[i].time_to_sleep = arg->time_to_sleep;
		philos[i].nb_eat = arg->nb_eat;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % arg->nb_philo];
		i++;
	}
	return (SUCCESS);
}

void	philo_sync_mon(t_philo *philos, t_mon_dead *mon_dead,
						t_mon_end *mon_end)
{
	int	i;

	i = 0;
	while (i < mon_dead->nb_philo)
	{
		philos[i].m_out_table = mon_end->m_out_table;
		philos[i].dead = &(mon_dead->has_dead);
		i++;
	}
}

// TODO : ERROR CODE ! 

t_philo	*init_philo(t_arg *arg)
{
	t_philo			*philos;
	pthread_mutex_t	*forks;

	philos = (t_philo *)malloc(sizeof(t_philo) * arg->nb_philo);
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * arg->nb_philo);
	if (!philos || !forks)
		return (NULL);
	if (init_fork_mutex(forks, arg->nb_philo) != SUCCESS)
		return (NULL);
	if (take_philo_arg(philos, forks, arg) != SUCCESS)
		return (NULL);
	return (philos);
}

//TODO Stop Thread

int	launch_philo(t_philo *philos, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_create(philos[i].thread, NULL, &philo_routine,
				&philos[i]) != SUCCESS)
			return (errno);
		pthread_detach(*(philos[i].thread));
		i++;
	}
	return (SUCCESS);
}
