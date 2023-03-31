/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:47:56 by afadlane          #+#    #+#             */
/*   Updated: 2023/03/31 14:22:05 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_dead(void *tmp)
{
	t_philo	*p;

	p = (t_philo *)tmp;
	while (1)
	{
		sem_wait(p->lock_time);
		if (gettime() - (p->time.tv_sec * 1000 + p->time.tv_usec
				/ 1000) > p->infop->time_to_die)
		{
			sem_wait(p->lock);
			printf("%ld Philo : %d is dead.\n", get_current_time(p), p->id);
			exit(1);
		}
		sem_post(p->lock_time);
		if (p->infop->time_must_eat != -1)
		{
			if (p->eaten >= p->infop->time_must_eat)
				exit(0);
		}
	}
	return (NULL);
}

void	split_ft_init(t_philo *p, t_info *info, t_philo *tmp, int i)
{
	p->id = i + 1;
	p->eaten = 0;
	p->infop = info;
	p->semaphore = tmp->semaphore;
	p->lock = tmp->lock;
	p->lock_time = tmp->lock_time;
}

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
		split_ft_init(p, info, tmp, i);
		gettimeofday(&p->time, NULL);
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
}

void	get_and_insia(t_info *p, char **av, int ac)
{
	p->number_of_philosophers = ft_atoi(av[1]);
	p->time_to_die = ft_atoi(av[2]);
	p->time_to_eat = ft_atoi(av[3]);
	p->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		p->time_must_eat = ft_atoi(av[5]);
	else
		p->time_must_eat = -1;
}
