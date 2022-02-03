/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:57:39 by lwyss             #+#    #+#             */
/*   Updated: 2022/02/03 16:23:30 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct data
{
	int	philo_total;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meals_needed;
}	t_data;

typedef struct philo
{
	int				number;
	pthread_t		*thread_id;
	pthread_mutex_t	left_fork;	
	pthread_mutex_t	right_fork;
	t_data			data;
}	t_philo;

t_data	init(char **av);
void	clean_exit(t_philo *philo, pthread_t *philo_thread, \
pthread_mutex_t *fork);
double	get_time(void);
long	get_time_ms(void);
long	atol(const char *s);

#endif
