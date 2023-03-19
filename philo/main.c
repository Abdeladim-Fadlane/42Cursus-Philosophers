/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:13:13 by afadlane          #+#    #+#             */
/*   Updated: 2023/03/18 16:38:01 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (pthread_mutex_init(&p->lock, NULL) != 0)
		printf("error\n");
}

long	gettime(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000) + (t.tv_usec / 1000);
}

long	get_time(t_philo *p)
{
	long	t;

	t = gettime();
	return (t - p->f_time);
}

void	ft_time(int time, t_philo *p)
{
	int	i;

	i = get_time(p);
	while (get_time(p) - i < time)
		usleep(100);
}

void	eat(t_philo *p)
{
	pthread_mutex_lock(&p->forks);
	pthread_mutex_lock(&p->infop->lock);
	printf("|| %ld || Philo : %d has taken a fork.\n", get_time(p), p->id);
	pthread_mutex_unlock(&p->infop->lock);
	pthread_mutex_lock(&p->left->forks);
	pthread_mutex_lock(&p->infop->lock);
	printf("|| %ld || Philo : %d has taken a fork.\n", get_time(p), p->id);
	printf("|| %ld || Philo : %d is eating. \n", get_time(p), p->id);
	p->time_eat = get_time(p);
	p->eaten++;
	pthread_mutex_unlock(&p->infop->lock);
	ft_time(p->infop->time_to_eat, p);
	pthread_mutex_unlock(&p->left->forks);
	pthread_mutex_unlock(&p->forks);
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
			if (get_time(p) - p->time_eat > p->infop->time_to_die)
			{
				printf("|| %ld || Philo : %d is dead.\n", get_time(p), p->id);
				return ;
			}
			pthread_mutex_unlock(&p->infop->lock);
			if (p->infop->time_must_eat != -1)
			{
				pthread_mutex_lock(&p->infop->lock);
				if (p->eaten >= p->infop->time_must_eat)
					eat++;
				pthread_mutex_unlock(&p->infop->lock);
				if (eat == p->infop->number_of_philosophers)
				{
					pthread_mutex_lock(&p->infop->lock);
					return ;
				}
				
			}
			i++;
			p = p->right;
		}
	}
	return ;
}

void	creat_thread(t_philo *p)
{
	pthread_t	*thread_id;
	int			i;
	long		time;

	thread_id = malloc(sizeof(pthread_t) * p->infop->number_of_philosophers);
	time = get_time(p);
	i = 1;
	while (i <= p->infop->number_of_philosophers)
	{
		p->f_time = time;
		p->time_eat = time - p->f_time;
		//printf(":::::-%ld----%ld--\n", time, get_time(p));
		if (pthread_create(&thread_id[i], NULL, thread_func, p) != 0)
			perror("Failed to create thread");
		pthread_detach(thread_id[i]);
		p = p->right;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo			*p;
	pthread_mutex_t	mutex;

	if (ac == 5 || ac == 6)
	{
		if (check_argv(av, ac) == 1)
		{
			printf("---error----");
			return (0);
		}
		pthread_mutex_init(&mutex, NULL);
		p = malloc(sizeof(t_philo));
		ft_init_philo(p, av, ac);
		creat_thread(p);
		check_dead(p);
		pthread_mutex_destroy(&mutex);
	}
	else
	{
		printf("error");
		return (0);
	}
}
