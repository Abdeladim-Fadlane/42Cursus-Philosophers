/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:47:56 by afadlane          #+#    #+#             */
/*   Updated: 2023/03/16 18:11:52 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_philo(t_philo *p, char **av, int ac)
{
	int		i;
	t_info	*info;
	t_philo	*tmp;

	info = malloc(sizeof(t_info));
	get_and_insia(info, av, ac);
	tmp = p;
	i = 0;
	while (i < info->number_of_philosophers)
	{
		if (pthread_mutex_init(&p->forks, NULL) != 0)
			printf("error\n");
		p->id = i + 1;
		p->eaten = 0;
		p->infop = info;
		if (i + 1 < info->number_of_philosophers)
		{
			p->right = malloc(sizeof(t_philo));
			p->right->left = p;
			p = p->right;
		}
		else
		{
			p->right = tmp;
			tmp->left = p;
		}
		i++;
	}
	p = tmp;
}

void	*thread_func(void *tmp)
{
	t_philo	*p;

	p = (t_philo *)tmp;
	if (p->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		eat(p);
		pthread_mutex_lock(&p->infop->lock);
		printf("|| %ld || Philo : %d is sleeping.  \n", get_time(p), p->id);
		pthread_mutex_unlock(&p->infop->lock);
		ft_time(p->infop->time_to_sleep, p);
		pthread_mutex_lock(&p->infop->lock);
		printf("|| %ld || Philo : %d is thinking.\n", get_time(p), p->id);
		pthread_mutex_unlock(&p->infop->lock);
	}
	return (NULL);
}

int	check_argv(char **av, int ac)
{
	int i;
	int j;

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