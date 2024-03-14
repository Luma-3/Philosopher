/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:07:53 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/14 17:37:49 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "core_data.h"

void	*philo_routine(void *arg);

void	*routine_dead(void *arg);

int		take_timestamp(struct timeval *start_time);

int		init_data(t_philo **philos, pthread_mutex_t **forks, struct timeval *time,
			int nb_philos);

int		init_philo(t_philo *philos, t_arg *args, pthread_mutex_t *forks,
			struct timeval *time);

int		init_fork_mutex(pthread_mutex_t *forks, int nb_philo);

int		launch_thread(t_philo *philos, int nb_philo);

void	wait_thread(t_philo *philos, int nb_philo);

#endif //PHILO_H