/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:39:39 by lwyss             #+#    #+#             */
/*   Updated: 2022/02/21 15:39:50 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_data	*data_init(char **av)
{
	t_data			*data;

	data = malloc(sizeof(t_data) * 1);
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
	sem_unlink(FORKS);
	data->forks = sem_open(FORKS, O_CREAT | O_EXCL, 0777, data->philo_total);
	sem_unlink(ACCESS);
	data->access = sem_open(ACCESS, O_CREAT | O_EXCL, 0777, 1);
	return (data);
}

t_philo	*philo_init(t_data *data)
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
	}
	return (philo);
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
