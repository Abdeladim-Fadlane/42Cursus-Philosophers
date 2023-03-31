/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:13:13 by afadlane          #+#    #+#             */
/*   Updated: 2023/03/31 15:42:15 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *p)
{
	pthread_mutex_lock(&p->forks);
	pthread_mutex_lock(&p->infop->lock);
	printf("%ld  Philo : %d has taken a fork.\n", get_current_time(p), p->id);
	pthread_mutex_unlock(&p->infop->lock);
	pthread_mutex_lock(&p->left->forks);
	pthread_mutex_lock(&p->infop->lock);
	printf("%ld  Philo : %d has taken a fork.\n", get_current_time(p), p->id);
	printf("%ld  Philo : %d is eating. \n", get_current_time(p), p->id);
	p->time_eat = get_current_time(p);
	p->eaten++;
	pthread_mutex_unlock(&p->infop->lock);
	sleep_time(p->infop->time_to_eat, p);
	pthread_mutex_unlock(&p->left->forks);
	pthread_mutex_unlock(&p->forks);
}

int	split_check_dead(t_philo *p, int *eat)
{
	if (p->infop->time_must_eat != -1)
	{
		pthread_mutex_lock(&p->infop->lock);
		if (p->eaten >= p->infop->time_must_eat)
			(*eat)++;
		pthread_mutex_unlock(&p->infop->lock);
		if (*eat == p->infop->number_of_philosophers)
		{
			pthread_mutex_lock(&p->infop->lock);
			return (0);
		}
	}
	return (1);
}

void	check_dead(t_philo *p)
{
	int	eat;
	int	i;

	while (1)
	{
		i = 0;
		eat = 0;
		while (i < p->infop->number_of_philosophers)
		{
			pthread_mutex_lock(&p->infop->lock);
			if (get_current_time(p) - p->time_eat > p->infop->time_to_die)
			{
				printf("%ld Philo : %d is dead.\n", get_current_time(p), p->id);
				return ;
			}
			pthread_mutex_unlock(&p->infop->lock);
			if (split_check_dead(p, &eat) == 0)
				return ;
			i++;
			p = p->right;
		}
	}
	return ;
}

void	creat_thread(t_philo *p, pthread_t *thread_id)
{
	int		i;
	long	time;

	time = get_current_time(p);
	i = 1;
	while (i <= p->infop->number_of_philosophers)
	{
		p->begin_time = time;
		if (pthread_create(&thread_id[i], NULL, thread_func, p) != 0)
			perror("Failed to create thread");
		p = p->right;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo			*p;
	pthread_mutex_t	mutex;
	pthread_t		*thread_id;

	if (ac == 5 || ac == 6)
	{
		thread_id = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
		if (check_argv(av, ac) == 1)
		{
			printf("---error----");
			return (0);
		}
		pthread_mutex_init(&mutex, NULL);
		p = malloc(sizeof(t_philo));
		ft_init_philo(p, av, ac);
		creat_thread(p, thread_id);
		check_dead(p);
		pthread_mutex_destroy(&mutex);
	}
	else
		printf("error");
}
