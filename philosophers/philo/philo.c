#include "philo.h"

void    *philo_routine(void *arg)
{
	static int	philo_created = 0;
	int			philo_number;
	double		time_to_die;
	philo_t		*philo;

	philo_number = ++philo_created;
	philo = (philo_t *)arg;
	time_to_die = get_time() + (philo->data.time_to_die * 0.001);
	printf("\033[44m%li %i is thinking\033[0m\n", get_time_ms(), philo_number);
	while (get_time() < time_to_die)
		;
	printf("\033[41m%li %i died\033[0m\n", get_time_ms(), philo_number);
    return (0);
}

int main(int ac, char **av)
{
	data_t			data;
	philo_t			*philo;
    pthread_t		*philo_thread;
	pthread_mutex_t	*fork;
	int				i;

    if (ac == 5 || ac == 6)
    {
        data.philo_total = atol(av[1]);
        data.time_to_die = atol(av[2]);
        data.time_to_eat = atol(av[3]);
        data.time_to_sleep = atol(av[4]);
		if (av[5])
        	data.meals_needed = atol(av[5]);
		philo = malloc(sizeof(philo_t) * data.philo_total);
		philo_thread = malloc(sizeof(pthread_t) * data.philo_total);
		fork = malloc(sizeof(pthread_mutex_t) * data.philo_total);
		i = -1;
		while (++i < data.philo_total)
		{
			philo[i].data = data;
			pthread_create(&philo_thread[i], NULL, philo_routine, &philo[i]);
			philo[i].philo_thread = &philo_thread[i];
			pthread_mutex_init(&fork[i], NULL);
			philo[i].left_fork = &fork[i];
			usleep(1);
		}
		i = -1;
		while (++i < data.philo_total)
			pthread_join(philo_thread[i], NULL);
		i = -1;
		while (++i < data.philo_total)
			pthread_mutex_destroy(&fork[i]);
		free(philo_thread);
    }
    return (0);
}

// printf("\033[...m------\033[0m\n"); ... = 41 -> 47 & 89 -> 97
