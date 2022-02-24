/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:41:45 by lwyss             #+#    #+#             */
/*   Updated: 2022/02/24 14:35:01 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

double	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec + (time.tv_usec * 0.000001));
}

long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec + (time.tv_usec * 0.000001)) * 1000);
}

void	eating(t_philo *philo)
{
	double		tmp;

	pthread_mutex_lock(philo->left_fork);
	if (!philo->data->dead)
		taking_fork(philo);
	pthread_mutex_lock(philo->right_fork);
	if (!philo->data->dead)
		taking_fork(philo);
	if (!philo->data->dead)
	{
		pthread_mutex_lock(philo->data->access);
		printf("\033[92m%li %i is eating\033[0m\n", \
		get_time_ms() - philo->data->start_time, philo->number);
		pthread_mutex_unlock(philo->data->access);
	}
	tmp = get_time();
	while (get_time() < tmp + (philo->data->time_to_eat * 0.001))
		usleep(500);
	if (!philo->data->dead)
		philo->last_meal = get_time();
	if (philo->data->meals_needed)
		philo->meals++;
}

void	sleeping(t_philo *philo)
{
	double		tmp;

	if (!philo->data->dead)
	{
		pthread_mutex_lock(philo->data->access);
		printf("\033[94m%li %i is sleeping\033[0m\n", \
		get_time_ms() - philo->data->start_time, philo->number);
		pthread_mutex_unlock(philo->data->access);
	}
	tmp = get_time();
	while (get_time() < tmp + (philo->data->time_to_sleep * 0.001))
		usleep(500);
}

void	thinking(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_total)
		printf("\033[95m0 %i is thinking\033[0m\n", i + 1);
}
