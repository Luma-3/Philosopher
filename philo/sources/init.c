/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:50:52 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/15 14:23:18 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_fork_mutex(pthread_mutex_t *forks, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != SUCCESS)
			return (errno); // TODO destroy mutex
		i++;
	}
	return (SUCCESS);
}

static int	init_philo(t_philo *philos,
						t_stdthread *std,
						pthread_mutex_t *forks,
						struct timeval *time)
{
	int	i;

	i = 0;
	while (i < std->args->nb_philo)
	{
		philos[i].thread = malloc(sizeof(pthread_t));
		philos[i].start_time_strave = malloc(sizeof(struct timeval));
		if (!(philos[i].thread) || !(philos[i].start_time_strave))
			return (ENOMEM); // TODO free .thread amd .start_time_strave
		gettimeofday(philos[i].start_time_strave, NULL);
		philos[i].id = i;
		philos[i].start_time = time;
		philos[i].dead = &(std->has_dead);
		philos[i].check_dead = std->dead;
		philos[i].time_to_eat = std->args->time_to_eat;
		philos[i].time_to_sleep = std->args->time_to_sleep;
		philos[i].nb_eat = std->args->nb_eat;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % std->args->nb_philo];
		i++;
	}
	return (SUCCESS);
}

int	init_data(struct timeval *time, t_stdthread *std)
{
	t_philo			*philos;
	pthread_mutex_t	*forks;

	philos = (t_philo *)malloc(sizeof(t_philo) * std->nb_philo);
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * std->nb_philo);
	if (!philos || !forks)
		return ((errno = ENOMEM), errno);
	if (gettimeofday(time, NULL) != 0)
		return (errno);
	if (init_fork_mutex(forks, std->nb_philo) != SUCCESS)
		return (errno);
	if (init_philo(philos, std, forks, time) != SUCCESS)
		return (errno);
	std->philos = philos;
	std->forks = forks;
	return (SUCCESS);
}

int	launch_thread(t_philo *philos, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_create(philos[i].thread, NULL, &philo_routine,
				&philos[i]) != SUCCESS)
			return (errno); //TODO Stop Thread
		i++;
	}
	return (SUCCESS);
}
