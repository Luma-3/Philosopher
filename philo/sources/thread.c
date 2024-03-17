/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:06:40 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/17 23:03:51 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	cal_time_die(t_philo *philo, t_stdthread *std)
{
	struct timeval	current_time;
	int				strave_tv_sec;
	int				strave_tv_usec;

	gettimeofday(&current_time, NULL);
	strave_tv_sec = current_time.tv_sec - philo->start_time_strave->tv_sec;
	strave_tv_usec = current_time.tv_usec - philo->start_time_strave->tv_usec;
	//printf("id = %d sec = %d usec = %d convert = %d\n", philo->id, strave_tv_sec, strave_tv_usec, strave_tv_sec * 1000 + strave_tv_usec / 1000);
	if (strave_tv_sec * 1000 + strave_tv_usec / 1000 >= std->time_to_die)
		return (true);
	return (false);
}

void	*routine_dead(void *arg)
{
	t_stdthread	*std;
	t_philo		*philos;
	int			i;

	std = (t_stdthread *)arg;
	philos = std->philos;
	while (true)
	{
		i = 0;
		while (i < std->nb_philo)
		{
			pthread_mutex_lock(std->dead);
			if (cal_time_die(&philos[i], std) == true)
			{
				std->has_dead = true;
				printf("%d %d died\n", take_timestamp(philos[i].start_time),
					philos[i].id);
				pthread_detach(*(philos[i].thread));
				//call function for stop all philo !
			}
			pthread_mutex_unlock(std->dead);
			if (std->has_dead == true)
				return (NULL);
			i++;
			usleep(1000);
		}
	}
	return (NULL);
}

void	wait_thread(t_philo *philos, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (philos[i].thread)
			pthread_join(*(philos[i].thread), NULL);
		free(philos[i].thread);
		i++;
	}
	free(philos);
}
