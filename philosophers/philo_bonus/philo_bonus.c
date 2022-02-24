/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:40:20 by lwyss             #+#    #+#             */
/*   Updated: 2022/02/24 14:14:01 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (!philo->data->dead)
	{
		if (!philo->data->dead)
			shortcut(philo);
		if (philo->data->meals_needed && \
		philo->meals == philo->data->meals_needed)
			return (0);
		if (!philo->data->dead)
			sleeping(philo);
		if (!philo->data->dead)
		{
			sem_wait(philo->data->access);
			printf("\033[95m%li %i is thinking\033[0m\n", \
			get_time_ms() - philo->data->start_time, philo->number);
			sem_post(philo->data->access);
		}
	}
	return (0);
}

static void	*checker_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (!philo->data->dead)
	{
		if (get_time() > philo->last_meal + (philo->data->time_to_die * 0.001))
			philo->data->dead = philo->number;
	}
	if (philo->data->meals_needed && philo->meals == philo->data->meals_needed)
		return (0);
	else
	{
		sem_wait(philo->data->access);
		printf("\033[91m%li %i died\033[0m\n", \
		get_time_ms() - philo->data->start_time, philo->data->dead);
	}
	return (0);
}

static void	philo_forked(t_philo *philo)
{
	pthread_t	routine;
	pthread_t	checker;

	if (philo->data->philo_total == 1)
	{
		printf("\033[93m%li %i has taken a fork\033[0m\n", \
		get_time_ms() - philo->data->start_time, philo->number);
		usleep(philo->data->time_to_die * 1000);
		printf("\033[91m%i %i died\033[0m\n", \
		philo->data->time_to_die, philo->number);
	}
	else
	{
		pthread_create(&checker, NULL, checker_routine, philo);
		pthread_create(&routine, NULL, philo_routine, philo);
		pthread_join(checker, NULL);
		pthread_join(routine, NULL);
	}
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
	t_data		*data;
	t_philo		*philo;
	int			pid;
	int			i;

	if (ac == 5 || ac == 6)
	{
		if (parsing(av))
			return (-1);
		data = data_init(av);
		philo = philo_init(data);
		pid = 1;
		i = -1;
		while (++i < data->philo_total && pid)
		{
			pid = fork();
			if (!pid)
				philo_forked(&philo[i]);
		}
		if (pid)
			clean_exit(data, philo);
	}
	return (0);
}
