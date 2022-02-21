/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:39:58 by lwyss             #+#    #+#             */
/*   Updated: 2022/02/21 15:40:10 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define FORKS "/forks"
# define ACCESS "/access"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>

typedef struct data
{
	int				philo_total;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_needed;
	long			start_time;
	int				dead;
	sem_t			*forks;
	sem_t			*access;
}	t_data;

typedef struct philo
{
	int				number;
	double			last_meal;
	t_data			*data;
}	t_philo;

t_data	*data_init(char **av);
t_philo	*philo_init(t_data *data);
double	get_time(void);
long	get_time_ms(void);
long	atol(const char *s);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	father(t_philo *philo);

#endif
