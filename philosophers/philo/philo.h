/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:57:39 by lwyss             #+#    #+#             */
/*   Updated: 2022/02/03 18:48:05 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct data
{
	int				philo_total;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_needed;
	long			start_time;
	int				dead;
	pthread_mutex_t	*access;
}	t_data;

typedef struct philo
{
	int				number;
	double			last_meal;
	pthread_t		thread_id;
	pthread_t		checker;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

t_data	*data_init(char **av);
t_philo *philo_init(t_data *data, pthread_mutex_t *fork);
void	clean_exit(t_philo *philo, pthread_mutex_t *fork);
void	*philo_routine(void *arg);
void	classical(t_philo *philo);
void	*checker_routine(void *arg);
void	taking_fork(t_philo *philo);
long	atol(const char *s);
double	get_time(void);
long	get_time_ms(void);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	optionnal(t_philo *philo);

#endif
