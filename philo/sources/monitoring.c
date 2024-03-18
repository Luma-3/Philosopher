/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:31:51 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/18 23:23:17 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	cal_time_die(t_philo *philo, int time_to_die)
{
	struct timeval	current_time;
	int				strave_tv_sec;
	int				strave_tv_usec;

	gettimeofday(&current_time, NULL);
	strave_tv_sec = current_time.tv_sec - philo->strave_time->tv_sec;
	strave_tv_usec = current_time.tv_usec - philo->strave_time->tv_usec;
	if (strave_tv_sec * 1000 + strave_tv_usec / 1000 >= time_to_die)
		return (true);
	return (false);
}

void	*dead_monitoring(void *arg)
{
	t_mon_dead	*mon_dead;
	int			i;

	mon_dead = (t_mon_dead *)arg;
	while (true)
	{
		i = 0;
		if (*(mon_dead->stop_mon) == true)
			break ;
		while (i < mon_dead->nb_philo)
		{
			if (cal_time_die(&(mon_dead->philos[i]),
					mon_dead->time_to_die) == true)
			{
				mon_dead->has_dead = true;
				printf("%d %d died\n",
					take_timestamp(mon_dead->philos[i].start_time),
					mon_dead->philos[i].id);
				return (NULL);
			}
			usleep(1000);
			i++;
		}
	}
	*(mon_dead->stop_mon) = true;
	return (NULL);
}

void	*end_monitoring(void *arg)
{
	t_mon_end	*mon_end;
	int			i;
	int			nb_exit;

	mon_end = (t_mon_end *)arg;
	pthread_mutex_lock(mon_end->m_out_table);
	while (true)
	{
		i = 0;
		nb_exit = 0;
		if (*(mon_end->stop_mon) == true)
			break ;
		while (i < mon_end->nb_philo)
		{
			if (mon_end->philos[i].nb_eat == 0)
				nb_exit++;
			i++;
		}
		usleep(1000);
		if (nb_exit == mon_end->nb_philo)
			break ;
	}
	*(mon_end->stop_mon) = true;
	pthread_mutex_unlock(mon_end->m_out_table);
	return (NULL);
}
