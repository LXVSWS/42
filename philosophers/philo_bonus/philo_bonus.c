#include "philo_bonus.h"

static void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (!philo->data->dead)
	{
		if (!philo->data->dead)
		{
			sem_wait(philo->data->access);
			printf("\033[95m%li %i is thinking\033[0m\n", get_time_ms() - philo->data->start_time, philo->number);
			sem_post(philo->data->access);
		}
		if (!philo->data->dead)
		{
			sem_wait(philo->data->forks);
			sem_wait(philo->data->forks);
			eating(philo);
			sem_post(philo->data->forks);
			sem_post(philo->data->forks);
		}
		if (!philo->data->dead)
			sleeping(philo);
	}
	return (0);
}

static void	*optionnal_routine(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	while (!philo->data->dead && i < philo->data->meals_needed)
	{
		if (!philo->data->dead)
			printf("\033[95m%li %i is thinking\033[0m\n", get_time_ms() - philo->data->start_time, philo->number);
		if (!philo->data->dead)
		{
			sem_wait(philo->data->forks);
			sem_wait(philo->data->forks);
			eating(philo);
			sem_post(philo->data->forks);
			sem_post(philo->data->forks);
		}
		i++;
		if (!philo->data->dead && i != philo->data->meals_needed)
			sleeping(philo);
	}
	if (philo->data->dead && i < philo->data->meals_needed)
		philo->data->meals_needed = -1;
	return (0);
}

static void	*checker_routine(void *arg)
{
	t_philo		*philo;
	long		saved_time;

	philo = (t_philo *)arg;
	while (!philo->data->dead)
	{
		if (get_time() > philo->last_meal + (philo->data->time_to_die * 0.001))
			philo->data->dead = philo->number;
	}
	sem_wait(philo->data->access);
	if (!philo->data->meals_needed)
	{
		printf("\033[91m%li %i died\033[0m\n", get_time_ms() - philo->data->start_time, philo->data->dead);
		return (0);
	}
	else
	{
		saved_time = get_time_ms() - philo->data->start_time;
		usleep(1000000);
	}
	if (philo->data->meals_needed == -1)
		printf("\033[91m%li %i died\033[0m\n", saved_time, philo->data->dead);
	return (0);
}

static void philo_forked(t_philo *philo)
{
	pthread_t	routine;
	pthread_t	checker;

	if (philo->data->philo_total == 1)
	{
		printf("\033[95m%li %i is thinking\033[0m\n", get_time_ms() - philo->data->start_time, philo->number);
		printf("\033[93m%li %i has taken a fork\033[0m\n", get_time_ms() - philo->data->start_time, philo->number);
		usleep(philo->data->time_to_die * 1000);
		printf("\033[91m%i %i died\033[0m\n", philo->data->time_to_die, philo->number);
	}
	else
	{
		if (!philo->data->meals_needed)
			pthread_create(&routine, NULL, philo_routine, philo);
		else
			pthread_create(&routine, NULL, optionnal_routine, philo);
		pthread_create(&checker, NULL, checker_routine, philo);
		pthread_join(routine, NULL);
		pthread_join(checker, NULL);
	}
}

int main(int ac, char **av)
{
	t_data		*data;
	t_philo		*philo;
	int			pid;
	int			i;

	if (ac == 5 || ac == 6)
	{
		data = data_init(av);
		philo = philo_init(data);
		pid = 1;
		i = -1;
		while (++i < data->philo_total && pid)
		{
			pid = fork();
			if (!pid)
				philo_forked(&philo[i]);
		}
		if (pid)
			father(philo);
	}
	return (0);
}
