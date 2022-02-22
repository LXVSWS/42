/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:57:26 by lwyss             #+#    #+#             */
/*   Updated: 2022/02/21 18:22:04 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_total == 1)
		printf("\033[93m%li %i has taken a fork\033[0m\n", \
		get_time_ms() - philo->data->start_time, philo->number);
	else
	{
		if (!philo->data->meals_needed)
			while (!philo->data->dead)
				routine(philo);
		else
			while (!philo->data->dead && philo->meals < philo->data->meals_needed)
				routine(philo);
	}
	return (0);
}

void	routine(t_philo *philo)
{
	if (!philo->data->dead)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		eating(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	if (philo->data->meals_needed && philo->meals == philo->data->meals_needed)
		return ;
	if (!philo->data->dead)
		sleeping(philo);
	if (!philo->data->dead)
	{
		pthread_mutex_lock(philo->data->access);
		printf("\033[95m%li %i is thinking\033[0m\n", \
		get_time_ms() - philo->data->start_time, philo->number);
		pthread_mutex_unlock(philo->data->access);
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
		if (!philo->data->dead && philo->data->meals_needed \
		&& philo->meals == philo->data->meals_needed)
			return (0);
	}
	pthread_mutex_lock(philo->data->access);
	if (!philo->data->printed)
	{
		printf("\033[91m%li %i died\033[0m\n", \
		get_time_ms() - philo->data->start_time, philo->data->dead);
		philo->data->printed = 1;
	}
	if (philo->data->printed)
		pthread_mutex_unlock(philo->data->access);
	return (0);
}

static int	parsing(char **av)
{
	int		i;
	int		y;

	i = 0;
	y = -1;
	while (av[++i])
	{
		while (av[i][++y])
		{
			if (av[i][y] < 48 || av[i][y] > 57)
				return (1);
		}
		y = -1;
		if (atol(av[i]) < -2147483648 || atol(av[i]) > 2147483647)
			return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data			*data;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	int				i;

	if (ac == 5 || ac == 6)
	{
		if (parsing(av))
			return (-1);
		data = data_init(av);
		fork = malloc(sizeof(pthread_mutex_t) * data->philo_total);
		philo = philo_init(data, fork);
		i = -1;
		while (++i < data->philo_total)
		{
			pthread_join(philo[i].thread_id, NULL);
			pthread_join(philo[i].checker, NULL);
		}
		clean_exit(data, fork, philo);
	}
	return (0);
}
