/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:57:26 by lwyss             #+#    #+#             */
/*   Updated: 2022/02/21 15:45:32 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_total == 1)
	{
		printf("\033[95m%li %i is thinking\033[0m\n", \
		get_time_ms() - philo->data->start_time, philo->number);
		printf("\033[93m%li %i has taken a fork\033[0m\n", \
		get_time_ms() - philo->data->start_time, philo->number);
	}
	else if (philo->data->meals_needed)
		optionnal(philo);
	else
		classical(philo);
	return (0);
}

void	classical(t_philo *philo)
{
	while (!philo->data->dead)
	{
		if (!philo->data->dead)
		{
			pthread_mutex_lock(philo->data->access);
			printf("\033[95m%li %i is thinking\033[0m\n", \
			get_time_ms() - philo->data->start_time, philo->number);
			pthread_mutex_unlock(philo->data->access);
		}
		if (!philo->data->dead)
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
			eating(philo);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
		}
		if (!philo->data->dead)
			sleeping(philo);
	}
}

void	*checker_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (!philo->data->dead)
	{
		if (get_time() > philo->last_meal + (philo->data->time_to_die * 0.001))
			philo->data->dead = philo->number;
	}
	return (0);
}

static void	*death_routine(void *arg)
{
	t_philo		*philo;
	long		saved_time;

	philo = (t_philo *)arg;
	while (!philo->data->dead)
		;
	pthread_mutex_lock(philo->data->access);
	if (!philo->data->meals_needed)
	{
		printf("\033[91m%li %i died\033[0m\n", \
		get_time_ms() - philo->data->start_time, philo->data->dead);
		return (0);
	}
	else
	{
		saved_time = get_time_ms() - philo->data->start_time;
		usleep(1000000);
	}
	if (philo->data->meals_needed == -1)
		printf("\033[91m%li %i died\033[0m\n", saved_time, philo->data->dead);
	return (0);
}

int	main(int ac, char **av)
{
	t_data			*data;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_t		death;
	int				i;

	if (ac == 5 || ac == 6)
	{
		data = data_init(av);
		fork = malloc(sizeof(pthread_mutex_t) * data->philo_total);
		philo = philo_init(data, fork);
		pthread_create(&death, NULL, death_routine, philo);
		pthread_join(death, NULL);
		i = -1;
		while (++i < data->philo_total)
		{
			pthread_join(philo[i].thread_id, NULL);
			pthread_join(philo[i].checker, NULL);
		}
		clean_exit(philo, fork);
	}
	return (0);
}
