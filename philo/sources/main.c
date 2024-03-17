/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:47:52 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/17 22:51:24 by jbrousse         ###   ########.fr       */
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

void	free_mutex(int nb, pthread_mutex_t *forks)
{
	while (nb > 1)
	{
		free(&forks[nb - 1]);
		nb--;
	}
}

int	start_pb(t_arg *arg)
{
	struct timeval	time;
	t_stdthread		std;
	pthread_t		thread_checker;
	pthread_mutex_t	dead_mutex;

	std.args = arg;
	std.nb_philo = arg->nb_philo;
	std.has_dead = false;
	std.dead = &dead_mutex;
	std.time_to_die = arg->time_to_die;
	pthread_mutex_init(std.dead, NULL);
	if (init_data(&time, &std) != SUCCESS)
		return (errno);
	if (launch_thread(std.philos, std.nb_philo) != SUCCESS)
		return (errno);
	pthread_create(&thread_checker, NULL, &routine_dead, &std);
	pthread_join(thread_checker, NULL);
	wait_thread(std.philos, arg->nb_philo);
	//free_mutex(std.nb_philo, std.forks);
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
