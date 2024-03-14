/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:47:52 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/14 17:38:05 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "philo.h"

int	take_timestamp(struct timeval *start_time)
{
	struct timeval	current_time;
	int				time_sec;
	int				time_usec;

	if (gettimeofday(&current_time, NULL) == -1)
		return (errno);
	time_sec = current_time.tv_sec - start_time->tv_sec;
	time_usec = current_time.tv_usec - start_time->tv_usec;
	return (time_sec * 1000 + time_usec / 1000);
}

int	start_pb(t_arg *arg)
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	struct timeval	time;
	t_stdthread		std;
	bool			has_dead;
	pthread_t		thread_checker;

	philos = NULL;
	forks = NULL;
	if (init_data(&philos, &forks, &time, arg->nb_philo) != SUCCESS)
		return (errno);
	if (init_fork_mutex(forks, arg->nb_philo) != SUCCESS)
		return (errno);
	std.philos = philos;
	pthread_mutex_init(std.dead, NULL);
	std.has_dead = &has_dead;
	std.args = arg;
	std.nb_philo = arg->nb_philo;
	if (init_philo(philos, &std, forks, &time) != SUCCESS)
		return (errno);
	if (launch_thread(philos, arg->nb_philo) != SUCCESS)
		return (errno);
	pthread_create(&thread_checker, NULL, &routine_dead, &std);
	wait_thread(philos, arg->nb_philo);
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_arg	arg;
	int		ret;

	ret = parser(ac, av, &arg);
	if (ret != 0)
		return (ret);
	if (start_pb(&arg) != SUCCESS)
		return (errno);
	return (0);
}
