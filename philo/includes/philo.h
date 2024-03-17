/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:07:53 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/15 11:29:33 by jbrousse         ###   ########.fr       */
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

int		launch_thread(t_philo *philos, int nb_philo);

void	wait_thread(t_philo *philos, int nb_philo);

int		init_data(struct timeval *time, t_stdthread *std);

#endif //PHILO_H