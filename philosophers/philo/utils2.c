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

	if (!philo->data->dead)
		taking_fork(philo);
	if (!philo->data->dead)
		taking_fork(philo);
	if (!philo->data->dead)
	{
		pthread_mutex_lock(philo->data->access);
		printf("\033[92m%li %i is eating\033[0m\n", get_time_ms() - philo->data->start_time, philo->number);
		pthread_mutex_unlock(philo->data->access);
	}
	tmp = get_time();
	while (get_time() < tmp + (philo->data->time_to_eat * 0.001))
		;
	if (!philo->data->dead)
		philo->last_meal = get_time();
}

void	sleeping(t_philo *philo)
{
	double		tmp;

	if (!philo->data->dead)
	{
		pthread_mutex_lock(philo->data->access);
		printf("\033[94m%li %i is sleeping\033[0m\n", get_time_ms() - philo->data->start_time, philo->number);
		pthread_mutex_unlock(philo->data->access);
	}
	tmp = get_time();
	while (get_time() < tmp + (philo->data->time_to_sleep * 0.001))
		;
}

void	optionnal(t_philo *philo)
{
	int			i;

	i = 0;
	while (!philo->data->dead && i < philo->data->meals_needed)
	{
		if (!philo->data->dead)
		{
			pthread_mutex_lock(philo->data->access);
			printf("\033[95m%li %i is thinking\033[0m\n", get_time_ms() - philo->data->start_time, philo->number);
			pthread_mutex_unlock(philo->data->access);
		}
		if (!philo->data->dead)
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
			eating(philo);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
		}
		i++;
		if (!philo->data->dead && i != philo->data->meals_needed)
			sleeping(philo);
	}
	if (philo->data->dead && i < philo->data->meals_needed)
		philo->data->meals_needed = -1;
}