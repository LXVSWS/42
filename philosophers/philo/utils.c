/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:57:45 by lwyss             #+#    #+#             */
/*   Updated: 2022/02/03 16:33:59 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init(char **av)
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
	pthread_mutex_init(access, NULL);
	data->access = access;
	return (data);
}

void	clean_exit(t_philo *philo, pthread_mutex_t *fork)
{
	int	i;

	i = -1;
	while (++i < philo->data->philo_total)
		pthread_mutex_destroy(&fork[i]);
	pthread_mutex_destroy(philo->data->access);
	free(philo);
	free(fork);
}

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
