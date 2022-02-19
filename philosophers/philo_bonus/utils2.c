#include "philo_bonus.h"

void	eating(t_philo *philo)
{
	if (!philo->data->dead)
		printf("\033[95m%li %i is thinking\033[0m\n", get_time_ms() - philo->data->start_time, philo->number);
	if (!philo->data->dead)
		printf("\033[93m%li %i has taken a fork\033[0m\n", get_time_ms() - philo->data->start_time, philo->number);
	if (!philo->data->dead)
		printf("\033[93m%li %i has taken a fork\033[0m\n", get_time_ms() - philo->data->start_time, philo->number);
	if (!philo->data->dead)
		printf("\033[92m%li %i is eating\033[0m\n", get_time_ms() - philo->data->start_time, philo->number);
}