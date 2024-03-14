/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:06:40 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/14 17:41:41 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_dead(void *arg)
{
	t_stdthread *std;
	int			nb_philo;
	int			i;
	struct timeval time;

	std = (t_stdthread *)arg;
	while (true)
	{
		i = 0;
		while (i < std->nb_philo)
		{
			pthread_mutex_lock(std->dead);
			gettimeofday(&time, NULL);
			if (std->philos[i].start_time_strave )
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
		pthread_join(*philos[i].thread, NULL);
		free(philos[i].thread);
		i++;
	}
	free(philos);
}
