/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:11:52 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/14 15:16:42 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	nb = 0;
	sign = 1;
	while ((8 < str[i] && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && (47 < str[i] && str[i] < 58))
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (nb * sign);
}

static int	verif_is_digit(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

static void	set_arg(t_arg *arg, char **av, int ac)
{
	arg->nb_philo = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		arg->nb_eat = ft_atoi(av[5]);
	else
		arg->nb_eat = -1;
}

int	parser(int ac, char **av, t_arg *arg)
{
	int		i;

	i = 0;
	if (ac < 5 || ac > 6)
	{
		errno = EARGC;
		return (EARGC);
	}
	while (i < ac - 1)
	{
		if (!verif_is_digit(av[i + 1]))
		{
			errno = EARGTYPE;
			return (EARGTYPE);
		}
		i++;
	}
	set_arg(arg, av, ac);
	return (0);
}
