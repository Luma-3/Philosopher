/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:21:43 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/18 23:19:53 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_mon_dead	*init_mon_dead(t_arg *arg, t_philo *philos, bool *stop_mon)
{
	t_mon_dead	*mon_dead;

	mon_dead = malloc(sizeof(t_mon_dead));
	if (!mon_dead)
	{
		errno = ENOMEM;
		return (NULL);
	}
	mon_dead->thread = malloc(sizeof(pthread_t));
	if (!mon_dead->thread)
	{
		errno = ENOMEM;
		return (NULL);
	}
	mon_dead->stop_mon = stop_mon;
	mon_dead->nb_philo = arg->nb_philo;
	mon_dead->has_dead = false;
	mon_dead->time_to_die = arg->time_to_die;
	mon_dead->philos = philos;
	return (mon_dead);
}

t_mon_end	*init_mon_end(t_arg *arg, t_philo *philos, bool *stop_mon)
{
	t_mon_end	*mon_end;

	mon_end = malloc(sizeof(t_mon_end));
	if (!mon_end)
	{
		errno = ENOMEM;
		return (NULL);
	}
	mon_end->thread = malloc(sizeof(pthread_t));
	mon_end->m_out_table = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mon_end->m_out_table, NULL);
	if (!mon_end->thread || !mon_end->m_out_table)
	{
		errno = ENOMEM;
		return (NULL);
	}
	mon_end->stop_mon = stop_mon;
	mon_end->nb_philo = arg->nb_philo;
	mon_end->philos = philos;
	return (mon_end);
}
