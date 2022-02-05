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
	t_philo		*philo;
	long		start_time;
	double		tmp;

	philo = (t_philo *)arg;
	start_time = get_time_ms();
	printf("\033[95m%li %i is thinking\033[0m\n", get_time_ms() - start_time, philo->number);
	while (!philo->dead && philo->left_fork && philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		if (!philo->dead)
		{
			printf("\033[93m%li %i has taken a fork\033[0m\n", get_time_ms() - start_time, philo->number);
			printf("\033[93m%li %i has taken a fork\033[0m\n", get_time_ms() - start_time, philo->number);
			printf("\033[92m%li %i is eating\033[0m\n", get_time_ms() - start_time, philo->number);			
		}
		tmp = get_time();
		while (get_time() < tmp + (philo->data.time_to_eat * 0.001))
			;
		philo->last_meal = get_time();
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (!philo->dead)
			printf("\033[94m%li %i is sleeping\033[0m\n", get_time_ms() - start_time, philo->number);
		while (get_time() < philo->last_meal + (philo->data.time_to_sleep * 0.001))
			;
		if (!philo->dead)
			printf("\033[95m%li %i is thinking\033[0m\n", get_time_ms() - start_time, philo->number);
	}
	return (0);
}

void	*checker_routine(void *arg)
{
	t_philo		*philo;
	long		start_time;
	int			philo_alive;
	int			i;

	philo = *(t_philo **)arg;
	start_time = get_time_ms();
	i = 0;
	if (philo->data.philo_total > 3)
	{
		philo_alive = philo->data.philo_total;
		while (philo_alive)
		{
			while (i < philo->data.philo_total)
			{
				if (get_time() > philo[i].last_meal + (philo->data.time_to_die * 0.001) && !philo[i].dead)
				{
					printf("\033[91m%li %i died\033[0m\n", get_time_ms() - start_time, philo[i].number);
					philo[i].dead = 1;
					philo_alive--;
				}
				i++;
			}
			i = 0;
		}
	}
	else if (philo->data.philo_total == 1)
	{
		philo[i].dead = 1;
		while (get_time() < philo[i].last_meal + (philo->data.time_to_die * 0.001))
			;
		printf("\033[91m%li %i died\033[0m\n", get_time_ms() - start_time, philo[i].number);
	}
	else if (philo->data.philo_total == 2)
	{
		philo[i].dead = 1;
		while (get_time() < philo[i].last_meal + (philo->data.time_to_die * 0.001))
			;
		printf("\033[91m%li %i died\033[0m\n", get_time_ms() - start_time, philo[i].number);
		i++;
		philo[i].dead = 1;
		while (get_time() < philo[i].last_meal + (philo->data.time_to_die * 0.001))
			;
		printf("\033[91m%li %i died\033[0m\n", get_time_ms() - start_time, philo[i].number);
	}
	else if (philo->data.philo_total == 3)
	{
		philo[i].dead = 1;
		while (get_time() < philo[i].last_meal + (philo->data.time_to_die * 0.001))
			;
		printf("\033[91m%li %i died\033[0m\n", get_time_ms() - start_time, philo[i].number);
		i++;
		philo[i].dead = 1;
			while (get_time() < philo[i].last_meal + (philo->data.time_to_die * 0.001))
			;
		printf("\033[91m%li %i died\033[0m\n", get_time_ms() - start_time, philo[i].number);
		i++;
		philo[i].dead = 1;
		while (get_time() < philo[i].last_meal + (philo->data.time_to_die * 0.001))
			;
		printf("\033[91m%li %i died\033[0m\n", get_time_ms() - start_time, philo[i].number);
	}
	return (arg);
}

int	main(int ac, char **av)
{
	t_data			data;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_t		checker;
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
			philo[i].data = data;
			philo[i].last_meal = get_time();
			pthread_create(&philo[i].thread_id, NULL, philo_routine, &philo[i]);
			pthread_mutex_init(&fork[i], NULL);
			philo[i].left_fork = &fork[i];
			if (data.philo_total == 1)
				philo[i].right_fork = NULL;
			else if (i == (data.philo_total - 1))
				philo[i].right_fork = &fork[0];
			else
				philo[i].right_fork = &fork[i + 1];
		}
		pthread_create(&checker, NULL, checker_routine, &philo);
		pthread_join(checker, NULL);
		i = -1;
		while (++i < data.philo_total)
			pthread_join(philo[i].thread_id, NULL);
		clean_exit(philo, fork);
	}
	return (0);
}

// printf("\033[...m------\033[0m\n"); ... = 41 -> 47 & 89 -> 97
