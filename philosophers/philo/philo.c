/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:57:26 by lwyss             #+#    #+#             */
/*   Updated: 2022/02/03 19:36:05 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void *arg)
{
	double		time_to_die;
	double		time_to_eat;
	double		time_to_sleep;
	t_philo		*philo;

	philo = (t_philo *)arg;
	time_to_die = get_time() + (philo->data.time_to_die * 0.001);
	while (get_time() < time_to_die)
	{
		printf("\033[95m%li %i is thinking\033[0m\n", get_time_ms(), philo->number);
		if (philo->left_fork && philo->right_fork)
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
			printf("\033[93m%li %i has taken a fork\033[0m\n", get_time_ms(), philo->number);
			printf("\033[93m%li %i has taken a fork\033[0m\n", get_time_ms(), philo->number);
			time_to_eat = get_time() + (philo->data.time_to_eat * 0.001);
			printf("\033[92m%li %i is eating\033[0m\n", get_time_ms(), philo->number);
			while (get_time() < time_to_eat)
				;
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			time_to_die = get_time() + (philo->data.time_to_die * 0.001);
			time_to_sleep = get_time() + (philo->data.time_to_sleep * 0.001);
			printf("\033[94m%li %i is sleeping\033[0m\n", get_time_ms(), philo->number);
			while (get_time() < time_to_sleep)
				;
		}
	}
	printf("\033[91m%li %i died\033[0m\n", get_time_ms(), philo->number);
	return (0);
}

int	main(int ac, char **av)
{
	t_data			data;
	t_philo			*philo;
	pthread_t		*thread_id;
	pthread_mutex_t	*fork;
	int				i;

	if (ac == 5 || ac == 6)
	{
		data = init(av);
		philo = malloc(sizeof(t_philo) * data.philo_total);
		thread_id = malloc(sizeof(pthread_t) * data.philo_total);
		fork = malloc(sizeof(pthread_mutex_t) * data.philo_total);
		i = -1;
		while (++i < data.philo_total)
		{
			philo[i].number = i + 1;
			philo[i].data = data;
			pthread_create(&philo[i].thread_id, NULL, philo_routine, &philo[i]);
			pthread_mutex_init(&fork[i], NULL);
			philo[i].left_fork = &fork[i];
			if (data.philo_total == 1)
				philo[i].right_fork = NULL;
			else if (i == (data.philo_total - 1))
				philo[i].right_fork = &fork[0];
			else
				philo[i].right_fork = &fork[i + 1];
			usleep(1);
		}
		i = -1;
		while (++i < data.philo_total)
			pthread_join(philo[i].thread_id, NULL);
		clean_exit(philo, thread_id, fork);
	}
	return (0);
}

// printf("\033[...m------\033[0m\n"); ... = 41 -> 47 & 89 -> 97
