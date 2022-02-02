#include "philo.h"

void    *philo_thread(void *arg)
{
	static int	philo_created = 0;
	int			philo_number;
	data		*data;
	double		clock;

	philo_number = ++philo_created;
	data = arg;
	clock = get_time() + (data->time_to_die * 0.001);
	printf("\033[44m%li %i is thinking\033[0m\n", get_time_ms(), philo_number);
	while (get_time() < clock)
		;
	printf("\033[41m%li %i died\033[0m\n", get_time_ms(), philo_number);
    pthread_exit(arg);
}

int main(int ac, char **av)
{
    pthread_t	*philo;
    data		data;
	int			i;

    if (ac == 5 || ac == 6)
    {
        data.philo_total = atol(av[1]);
        data.time_to_die = atol(av[2]);
        data.time_to_eat = atol(av[3]);
        data.time_to_sleep = atol(av[4]);
		if (av[5])
        	data.meals_needed = atol(av[5]);
		philo = malloc(sizeof(pthread_t) * data.philo_total);
		i = -1;
		while (++i < data.philo_total)
		{
			pthread_create(&philo[i], NULL, philo_thread, &data);
			usleep(1);
		}
		pthread_join(*philo, NULL);
		free(philo);
    }
    return (0);
}

// printf("\033[...m------\033[0m\n"); ... = 41 -> 47 & 89 -> 97