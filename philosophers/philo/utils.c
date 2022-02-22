/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:57:45 by lwyss             #+#    #+#             */
/*   Updated: 2022/02/21 17:30:45 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*data_init(char **av)
{
	t_data			*data;
	pthread_mutex_t	*access;

	data = malloc(sizeof(t_data) * 1);
	access = malloc(sizeof(pthread_mutex_t) * 1);
	data->philo_total = atol(av[1]);
	data->time_to_die = atol(av[2]);
	data->time_to_eat = atol(av[3]);
	data->time_to_sleep = atol(av[4]);
	if (av[5])
		data->meals_needed = atol(av[5]);
	else
		data->meals_needed = 0;
	data->start_time = get_time_ms();
	data->dead = 0;
	data->printed = 0;
	pthread_mutex_init(access, NULL);
	data->access = access;
	return (data);
}

t_philo	*philo_init(t_data *data, pthread_mutex_t *fork)
{
	t_philo			*philo;
	int				i;

	philo = malloc(sizeof(t_philo) * data->philo_total);
	i = -1;
	while (++i < data->philo_total)
		printf("\033[95m0 %i is thinking\033[0m\n", i + 1);
	i = -1;
	while (++i < data->philo_total)
	{
		philo[i].number = i + 1;
		philo[i].last_meal = get_time();
		philo[i].meals = 0;
		philo[i].data = data;
		pthread_mutex_init(&fork[i], NULL);
		philo[i].left_fork = &fork[i];
		if (data->philo_total > 1 && (i != (data->philo_total - 1)))
		{
			pthread_mutex_init(&fork[i + 1], NULL);
			philo[i].right_fork = &fork[i + 1];
		}
		else if (data->philo_total > 1 && (i == (data->philo_total - 1)))
			philo[i].right_fork = &fork[0];
		pthread_create(&philo[i].thread_id, NULL, philo_routine, &philo[i]);
		pthread_create(&philo[i].checker, NULL, checker_routine, &philo[i]);
	}
	return (philo);
}

void	clean_exit(t_philo *philo, pthread_mutex_t *fork)
{
	int				i;

	pthread_mutex_destroy(philo->data->access);
	i = -1;
	while (++i < philo->data->philo_total)
	{
		if (philo[i].left_fork)
			pthread_mutex_destroy(philo[i].left_fork);
		if (philo[i].right_fork)
			pthread_mutex_destroy(philo[i].right_fork);
	}
	free(philo->data->access);
	free(philo->data);
	free(fork);
	free(philo);
}

void	taking_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->data->access);
	printf("\033[93m%li %i has taken a fork\033[0m\n", \
	get_time_ms() - philo->data->start_time, philo->number);
	pthread_mutex_unlock(philo->data->access);
}

long	atol(const char *s)
{
	int			i;
	int			neg;
	long		res;

	i = 0;
	neg = 0;
	res = 0;
	while (s[i] == '\v' || s[i] == '\n' || s[i] == '\t' \
	|| s[i] == '\r' || s[i] == '\f' || s[i] == ' ')
		i++;
	if (s[i] == '-' && (s[i + 1] >= '0' && s[i] <= '9'))
	{
		neg++;
		i++;
	}
	if (s[i] == '+' && (s[i + 1] >= '0' && s[i] <= '9'))
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res *= 10;
		res += (s[i++] - 48);
	}
	if (neg == 1)
		return (-res);
	return (res);
}
