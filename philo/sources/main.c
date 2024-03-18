/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:47:52 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/18 23:16:38 by jbrousse         ###   ########.fr       */
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

int	start_dinner(t_arg *arg)
{
	t_philo			*philos;
	t_mon_dead		*mon_dead;
	t_mon_end		*mon_end;
	bool			stop_mon;

	philos = init_philo(arg);
	stop_mon = false;
	mon_dead = init_mon_dead(arg, philos, &stop_mon);
	mon_end = init_mon_end(arg, philos, &stop_mon);
	philo_sync_mon(philos, mon_dead, mon_end);
	if (launch_philo(philos, arg->nb_philo) != SUCCESS)
		return (errno);
	pthread_create(mon_dead->thread, NULL, &dead_monitoring, mon_dead);
	pthread_create(mon_end->thread, NULL, &end_monitoring, mon_end);
	pthread_join(*(mon_end->thread), NULL);
	pthread_join(*(mon_dead->thread), NULL);
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_arg		arg;
	int			ret;

	ret = parser(ac, av, &arg);
	if (ret != 0)
		return (ret);
	if (start_dinner(&arg) != SUCCESS)
		return (errno);
	return (0);
}
