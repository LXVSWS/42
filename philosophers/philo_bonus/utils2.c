/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:33:24 by lwyss             #+#    #+#             */
/*   Updated: 2022/02/21 15:38:46 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	shortcut(t_philo *philo)
{
	sem_wait(philo->data->forks);
	sem_wait(philo->data->forks);
	eating(philo);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

static void	taking_fork(t_philo *philo)
{
	sem_wait(philo->data->access);
	printf("\033[93m%li %i has taken a fork\033[0m\n", \
	get_time_ms() - philo->data->start_time, philo->number);
	sem_post(philo->data->access);
}

void	eating(t_philo *philo)
{
	double	tmp;

	if (!philo->data->dead)
		taking_fork(philo);
	if (!philo->data->dead)
		taking_fork(philo);
	if (!philo->data->dead)
	{
		sem_wait(philo->data->access);
		printf("\033[92m%li %i is eating\033[0m\n", \
		get_time_ms() - philo->data->start_time, philo->number);
		sem_post(philo->data->access);
	}
	tmp = get_time();
	while (get_time() < tmp + (philo->data->time_to_eat * 0.001))
		;
	if (!philo->data->dead)
		philo->last_meal = get_time();
	if (philo->data->meals_needed)
		philo->meals++;
}

void	sleeping(t_philo *philo)
{
	double	tmp;

	if (!philo->data->dead)
	{
		sem_wait(philo->data->access);
		printf("\033[94m%li %i is sleeping\033[0m\n", \
		get_time_ms() - philo->data->start_time, philo->number);
		sem_post(philo->data->access);
	}
	tmp = get_time();
	while (get_time() < tmp + (philo->data->time_to_sleep * 0.001))
		;
}

void	clean_exit(t_data *data, t_philo *philo)
{
	waitpid(0, NULL, 0);
	sem_close(data->forks);
	sem_close(data->access);
	sem_unlink(FORKS);
	sem_unlink(ACCESS);
	free(data);
	if (philo)
		free(philo);
}
