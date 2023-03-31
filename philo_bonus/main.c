/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:13:13 by afadlane          #+#    #+#             */
/*   Updated: 2023/03/31 14:20:23 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *p)
{
	sem_wait(p->semaphore);
	sem_wait(p->lock);
	printf("%ld  Philo : %d has taken a fork.\n", get_current_time(p), p->id);
	sem_post(p->lock);
	sem_wait(p->semaphore);
	sem_wait(p->lock);
	printf("%ld  Philo : %d has taken a fork.\n", get_current_time(p), p->id);
	sem_post(p->lock);
	gettimeofday(&p->time, NULL);
	sem_wait(p->lock);
	printf("%ld  Philo : %d is eating. \n", get_current_time(p), p->id);
	sem_post(p->lock);
	sleep_time(p->infop->time_to_eat);
	p->eaten++;
	sem_post(p->semaphore);
	sem_post(p->semaphore);
}

void	tthread_func(t_philo *p)
{
	pthread_t	*thread_id;

	thread_id = malloc(sizeof(pthread_t));
	if (pthread_create(thread_id, NULL, check_dead, p) != 0)
		perror("Failed to create thread");
	while (1)
	{
		eat(p);
		sem_wait(p->lock);
		printf("%ld  Philo : %d is sleeping.  \n", get_current_time(p), p->id);
		sem_post(p->lock);
		sleep_time(p->infop->time_to_sleep);
		sem_wait(p->lock);
		printf("%ld  Philo : %d is thinking.\n", get_current_time(p), p->id);
		sem_post(p->lock);
	}
}

void	wait_eat(t_philo *p)
{
	int	y;
	int	h;

	y = 0;
	while (waitpid(-1, &h, 0) != -1)
	{
		if (WEXITSTATUS(h) == 1)
		{
			while (y++ < p->infop->number_of_philosophers)
			{
				kill(p->pid, 9);
				p = p->right;
			}
		}
	}
}

void	creat_proccess(t_philo *p)
{
	int		i;
	long	time;
	pid_t	id;

	time = gettime();
	i = 1;
	while (i <= p->infop->number_of_philosophers)
	{
		p->begin_time = time;
		id = fork();
		if (id == 0)
			tthread_func(p);
		else
			p->pid = id;
		p = p->right;
		i++;
	}
	wait_eat(p);
}

int	main(int ac, char **av)
{
	t_philo	*p;

	p = malloc(sizeof(t_philo));
	if (ac == 5 || ac == 6)
	{
		p->semaphore = sem_open("/my_semaphore", O_CREAT, 0644, ft_atoi(av[1]));
		p->lock = sem_open("/lock", O_CREAT, 0644, 1);
		p->lock_time = sem_open("/lock_time", O_CREAT, 0644, 1);
		sem_unlink("/lock_time");
		sem_unlink("/my_semaphore");
		sem_unlink("/lock");
		if (check_argv(av, ac) == 1)
		{
			printf("---error----");
			return (0);
		}
		ft_init_philo(p, av, ac);
		p->eaten = 0;
		creat_proccess(p);
	}
	else
		printf("error");
	sem_close(p->semaphore);
}
