/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:44:47 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/14 17:42:34 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_sleep(int time_to_sleep, struct timeval *start_time, int id)
{
	printf("%d %d is sleeping\n", take_timestamp(start_time), id);
	usleep(time_to_sleep * 1000);
}

static void	take_fork(pthread_mutex_t *fork, struct timeval *start_time, int id)
{
	printf("%d %d has taken a fork\n", take_timestamp(start_time), id);
	pthread_mutex_lock(fork);
}

static void	eating(t_philo *philo, int time_to_eat, struct timeval *start_time, int id)
{
	struct timeval	time;

	printf("%d %d is eating\n", take_timestamp(start_time), id);
	usleep(time_to_eat * 1000);
	gettimeofday(&time, NULL);
	philo->start_time_strave = time;
}

static void	start_thinking(t_philo *philo)
{
	printf("%d %d is thinking\n", take_timestamp(philo->start_time), philo->id);
	take_fork(philo->left_fork, philo->start_time, philo->id);
	take_fork(philo->right_fork, philo->start_time, philo->id);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		nb_eat;

	philo = (t_philo *)arg;
	nb_eat = 0;
	while (true)
	{
		if (nb_eat <= philo->nb_eat)
			break ;
		start_thinking(philo);
		eating(philo, philo->time_to_eat, philo->start_time, philo->id);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		philo_sleep(philo->time_to_sleep, philo->start_time, philo->id);
		nb_eat++;
	}
	return (NULL);
}
