#include "philo.h"

double	get_time()
{
    struct timeval	time;

    gettimeofday(&time, NULL);
    return (time.tv_sec + (time.tv_usec * 0.000001));
}

void    *philo_thread(void *arg)
{
	static int	philo_created = 0;
	int			philo_number;
	data		*data;

	data = arg;
	philo_number = ++philo_created;
	printf("\033[44m%lf %i is thinking\033[0m\n", get_time(), philo_number);
	printf("\033[41m%lf %i died\033[0m\n", get_time(), philo_number);
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
			pthread_create(&philo[i], NULL, philo_thread, &data);
		i = -1;
		pthread_join(*philo, NULL);
		free(philo);
    }
    return (0);
}

// printf("\033[...m------\033[0m\n"); ... = 41 -> 47 & 89 -> 97