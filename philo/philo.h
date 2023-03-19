/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:03:33 by afadlane          #+#    #+#             */
/*   Updated: 2023/03/17 15:31:20 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef struct s_info
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_must_eat;
	pthread_mutex_t	mutex;
	pthread_mutex_t	lock;

}					t_info;

typedef struct s_philo
{
	int				id;
	int				eaten;
	struct s_philo	*left;
	struct s_philo	*right;
	pthread_mutex_t	forks;
	struct s_info	*infop;
	long			f_time;
	long			time_eat;
}					t_philo;

long				ft_atoi(char *str);
void				ft_init_philo(t_philo *p, char **av, int ac);
void				*thread_func(void *tmp);
void				get_and_insia(t_info *p, char **av, int ac);
void				eat(t_philo *p);
long				get_time(t_philo *p);
void				ft_time(int time, t_philo *p);
int					check_argv(char **av, int ac);
#endif
