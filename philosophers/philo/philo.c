/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:57:26 by lwyss             #+#    #+#             */
/*   Updated: 2022/02/03 16:35:43 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void *arg)
{
	double		time_to_die;
	t_philo		*philo;

	philo = (t_philo *)arg;
	time_to_die = get_time() + (philo->data.time_to_die * 0.001);
	printf("\033[44m%li %i is thinking\033[0m\n", get_time_ms(), philo->number);
	while (get_time() < time_to_die)
		;
	printf("\033[41m%li %i died\033[0m\n", get_time_ms(), philo->number);
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
			pthread_create(&thread_id[i], NULL, philo_routine, &philo[i]);
			philo[i].thread_id = &thread_id[i];
			pthread_mutex_init(&fork[i], NULL);
			philo[i].left_fork = fork[i];
			usleep(1);
		}
		i = -1;
		while (++i < data.philo_total)
			pthread_join(thread_id[i], NULL);
		clean_exit(philo, thread_id, fork);
	}
	return (0);
}

// printf("\033[...m------\033[0m\n"); ... = 41 -> 47 & 89 -> 97
