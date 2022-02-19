#include "philo_bonus.h"

static void taking_fork(t_philo *philo)
{
	sem_wait(philo->data->access);
	printf("\033[93m%li %i has taken a fork\033[0m\n", get_time_ms() - philo->data->start_time, philo->number);
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
		printf("\033[92m%li %i is eating\033[0m\n", get_time_ms() - philo->data->start_time, philo->number);
		sem_post(philo->data->access);
	}
	tmp = get_time();
	while (get_time() < tmp + (philo->data->time_to_eat * 0.001))
		;
	if (!philo->data->dead)
		philo->last_meal = get_time();
}

void	sleeping(t_philo *philo)
{
	double	tmp;

	if (!philo->data->dead)
	{
		sem_wait(philo->data->access);
		printf("\033[94m%li %i is sleeping\033[0m\n", get_time_ms() - philo->data->start_time, philo->number);
		sem_post(philo->data->access);
	}
	tmp = get_time();
	while (get_time() < tmp + (philo->data->time_to_sleep * 0.001))
		;
}

void	father(t_philo *philo)
{
	waitpid(-1, NULL, 0);
	sem_close(philo->data->forks);
	sem_close(philo->data->access);
	sem_unlink(FORKS);
	sem_unlink(ACCESS);
	free(philo->data);
	free(philo);
}
