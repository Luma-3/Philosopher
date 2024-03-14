/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:55:18 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/14 17:31:30 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_DATA_H
# define CORE_DATA_H

# include <pthread.h>
# include <sys/time.h>
# include <errno.h>
# include <stdbool.h>

# define SUCCESS 0
# define FAILURE -1

typedef struct s_philo
{
	int				id;
	struct timeval 	*start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				start_time_strave;
	int				nb_eat;
	bool			*dead;
	pthread_t		*thread;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
	pthread_mutex_t	*check_dead;
}			t_philo;

typedef struct s_arg
{
	int		nb_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_eat;
}			t_arg;

typedef struct s_stdthread
{
	int				nb_philo;
	bool			*has_dead;
	t_philo			*philos;
	t_arg			*args;
	pthread_mutex_t *dead;
	pthread_mutex_t	*std_out;
}					t_stdthread;

#endif