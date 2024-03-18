/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:55:18 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/18 22:48:28 by jbrousse         ###   ########.fr       */
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
	struct timeval	*start_time;
	int				time_to_eat;
	int				time_to_sleep;
	struct timeval	*strave_time;
	int				nb_eat;
	bool			*dead;
	pthread_t		*thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*m_out_table;
}			t_philo;

typedef struct s_arg
{
	int		nb_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_eat;
}			t_arg;

typedef struct s_mon_dead
{
	pthread_t		*thread;
	bool			*stop_mon;
	int				nb_philo;
	int				time_to_die;
	bool			has_dead;
	t_philo			*philos;
}					t_mon_dead;

typedef struct s_mon_end
{
	pthread_t		*thread;
	bool			*stop_mon;
	int				nb_philo;
	pthread_mutex_t	*m_out_table;
	t_philo			*philos;
}					t_mon_end;

#endif