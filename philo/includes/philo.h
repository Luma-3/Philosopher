/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:07:53 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/18 23:16:11 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "core_data.h"

void		*philo_routine(void *arg);

int			take_timestamp(struct timeval *start_time);

t_philo		*init_philo(t_arg *arg);

int			launch_philo(t_philo *philos, int nb_philo);

t_mon_end	*init_mon_end(t_arg *arg, t_philo *philos, bool *stop_mon);

t_mon_dead	*init_mon_dead(t_arg *arg, t_philo *philos, bool *stop_mon);

void		philo_sync_mon(t_philo *philos, t_mon_dead *mon_dead,
				t_mon_end *mon_end);

void		*end_monitoring(void *arg);

void		*dead_monitoring(void *arg);

#endif //PHILO_H