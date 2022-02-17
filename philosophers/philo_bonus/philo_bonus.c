#include "philo_bonus.h"

static t_data	*data_init(char **av)
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
	return (data);
}

static t_philo *philo_init(t_data *data)
{
	t_philo			*philo;
	int				i;

	philo = malloc(sizeof(t_philo) * data->philo_total);
	i = -1;
	while (++i < data->philo_total)
	{
		philo[i].number = i + 1;
		philo[i].last_meal = get_time();
		philo[i].data = data;
	}
	return (philo);
}

int main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	if (ac == 5 || ac == 6)
	{
		data = data_init(av);
		philo = philo_init(data);	
		printf("%i\n", data->philo_total);
	}
	return (0);
}
