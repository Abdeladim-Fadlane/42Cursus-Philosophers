/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:57:26 by afadlane          #+#    #+#             */
/*   Updated: 2023/03/31 14:24:05 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_argv(char **av, int ac)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		if (av[i][j] == '+')
			j++;
		while (av[i][++j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (1);
		}
		i++;
	}
	if (ac == 6)
		return (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0
			|| ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0
			|| ft_atoi(av[5]) <= 0);
	if (ac == 5)
		return (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0
			|| ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0);
	return (0);
}

long	ft_atoi(char *str)
{
	long				i;
	long				res;
	unsigned long long	sn;

	if (!str)
		return (0);
	i = 0;
	res = 0;
	sn = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sn = sn * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sn);
}

long	gettime(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long	get_current_time(t_philo *p)
{
	long	t;

	t = gettime();
	return (t - p->begin_time);
}

void	sleep_time(long time)
{
	long	i;

	i = gettime();
	while (gettime() - i < time)
		usleep(100);
}
