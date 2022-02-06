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

void	eating(t_philo *philo)
{
	double		tmp;

	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->data.access);
	if (!philo->data.dead)
		printf("\033[93m%li %i has taken a fork\033[0m\n", get_time_ms() - philo->data.start_time, philo->number);	
	pthread_mutex_unlock(&philo->data.access);	
	pthread_mutex_lock(&philo->data.access);
	if (!philo->data.dead)
		printf("\033[93m%li %i has taken a fork\033[0m\n", get_time_ms() - philo->data.start_time, philo->number);
	pthread_mutex_unlock(&philo->data.access);
	if (!philo->data.dead)
	{
		pthread_mutex_lock(&philo->data.access);
		printf("\033[92m%li %i is eating\033[0m\n", get_time_ms() - philo->data.start_time, philo->number);
		pthread_mutex_unlock(&philo->data.access);
	}
	tmp = get_time();
	while (get_time() < tmp + (philo->data.time_to_eat * 0.001))
		;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (!philo->data.dead)
		philo->last_meal = get_time();
}

void	sleeping(t_philo *philo)
{
	double		tmp;

	if (!philo->data.dead)
	{
		pthread_mutex_lock(&philo->data.access);
		printf("\033[94m%li %i is sleeping\033[0m\n", get_time_ms() - philo->data.start_time, philo->number);
		pthread_mutex_unlock(&philo->data.access);
	}
	tmp = get_time();
	while (get_time() < tmp + (philo->data.time_to_sleep * 0.001))
		;
}

static void	*philo_routine(void *arg)
{
	t_philo		*philo;
	int			i;

	philo = (t_philo *)arg;
	i = 0;
	if (philo->data.philo_total == 1)
	{
		printf("\033[95m%li %i is thinking\033[0m\n", get_time_ms() - philo->data.start_time, philo->number);
		printf("\033[93m%li %i has taken a fork\033[0m\n", get_time_ms() - philo->data.start_time, philo->number);
	}
	else if (philo->data.meals_needed)
	{
		while (!philo->data.dead && i < philo->data.meals_needed)
		{
			if (!philo->data.dead)
			{
				pthread_mutex_lock(&philo->data.access);
				printf("\033[95m%li %i is thinking\033[0m\n", get_time_ms() - philo->data.start_time, philo->number);
				pthread_mutex_unlock(&philo->data.access);
			}
			if (!philo->data.dead)
				eating(philo);
			i++;
			if (!philo->data.dead)
				sleeping(philo);
		}
	}
	else
	{
		while (!philo->data.dead)
		{
			if (!philo->data.dead)
			{
				pthread_mutex_lock(&philo->data.access);
				printf("\033[95m%li %i is thinking\033[0m\n", get_time_ms() - philo->data.start_time, philo->number);
				pthread_mutex_unlock(&philo->data.access);
			}
			if (!philo->data.dead)
				eating(philo);
			if (!philo->data.dead)
				sleeping(philo);
		}
	}
	return (0);
}

void	*checker_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (!philo->data.dead)
		if (get_time() > philo->last_meal + (philo->data.time_to_die * 0.001))
		{
			pthread_mutex_lock(&philo->data.access);
			philo->data.dead = philo->number;
			pthread_mutex_unlock(&philo->data.access);
		}
	return (0);
}

void	*death_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (!philo->data.dead)
		;
	pthread_mutex_lock(&philo->data.access);
	if (!philo->data.meals_needed)
		printf("\033[91m%li %i died\033[0m\n", get_time_ms() - philo->data.start_time, philo->data.dead);
	usleep(1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data			data;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_t		death;
	int				i;

	if (ac == 5 || ac == 6)
	{
		data = init(av);
		philo = malloc(sizeof(t_philo) * data.philo_total);
		fork = malloc(sizeof(pthread_mutex_t) * data.philo_total);
		i = -1;
		while (++i < data.philo_total)
		{
			philo[i].number = i + 1;
			philo[i].last_meal = get_time();
			philo[i].data = data;
			pthread_create(&philo[i].thread_id, NULL, philo_routine, &philo[i]);
			pthread_create(&philo[i].checker, NULL, checker_routine, &philo[i]);
			pthread_mutex_init(&fork[i], NULL);
			philo[i].left_fork = &fork[i];
			if (data.philo_total == 1)
				philo[i].right_fork = NULL;
			else if (data.philo_total > 1 && i == (data.philo_total - 1))
				philo[i].right_fork = &fork[0];
			else
				philo[i].right_fork = &fork[i + 1];
		}
		pthread_create(&death, NULL, death_routine, philo);
		pthread_join(death, NULL);
		i = -1;
		while (++i < data.philo_total)
		{
			pthread_join(philo[i].thread_id, NULL);
			pthread_join(philo[i].checker, NULL);
		}
		clean_exit(philo, fork);
	}
	return (0);
}

// printf("\033[...m------\033[0m\n"); ... = 41 -> 47 & 89 -> 97
