#include "philo_bonus.h"

static void	philo_routine(t_philo *philo)
{
	double		tmp;

	while (!philo->data->dead)
	{
		eating(philo);
		tmp = get_time();
		while (get_time() < tmp + (philo->data->time_to_eat * 0.001))
			;
		if (!philo->data->dead)
			philo->last_meal = get_time();
		if (!philo->data->dead)
			printf("\033[94m%li %i is sleeping\033[0m\n", get_time_ms() - philo->data->start_time, philo->number);
		tmp = get_time();
		while (get_time() < tmp + (philo->data->time_to_sleep * 0.001))
			;
	}
}

static void	*death_routine(void *arg)
{
	t_philo		*philo;
	long		saved_time;

	philo = (t_philo *)arg;
	while (!philo->data->dead)
	{
		if (get_time() > philo->last_meal + (philo->data->time_to_die * 0.001))
			philo->data->dead = philo->number;
	}
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

void	optionnal_routine(t_philo *philo)
{
	int			i;
	double		tmp;

	i = 0;
	while (!philo->data->dead && i < philo->data->meals_needed)
	{
		eating(philo);
		tmp = get_time();
		while (get_time() < tmp + (philo->data->time_to_eat * 0.001))
			;
		if (!philo->data->dead)
			philo->last_meal = get_time();
		if (philo->data->dead && i < philo->data->meals_needed)
			philo->data->meals_needed = -1;
		i++;
		if (!philo->data->dead && i != philo->data->meals_needed)
			printf("\033[94m%li %i is sleeping\033[0m\n", get_time_ms() - philo->data->start_time, philo->number);
		tmp = get_time();
		while (get_time() < tmp + (philo->data->time_to_sleep * 0.001))
			;
	}
}

static void philo_forked(t_philo *philo)
{
	pthread_t	death;

	if (philo->data->philo_total == 1)
	{
		printf("\033[95m%li %i is thinking\033[0m\n", get_time_ms() - philo->data->start_time, philo->number);
		printf("\033[93m%li %i has taken a fork\033[0m\n", get_time_ms() - philo->data->start_time, philo->number);
		usleep(philo->data->time_to_die * 1000);
		printf("\033[91m%i %i died\033[0m\n", philo->data->time_to_die, philo->number);
	}
	else
	{
		pthread_create(&death, NULL, death_routine, philo);
		if (philo->data->meals_needed)
			optionnal_routine(philo);
		else
			philo_routine(philo);
		pthread_join(death, NULL);
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
			waitpid(-1, NULL, 0);
	}
	return (0);
}
