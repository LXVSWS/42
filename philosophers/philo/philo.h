#ifndef PHILO__H
# define PHILO__H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	data
{
    int     philo_total;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
    int     meals_needed;
}				data_t;

typedef struct	philo
{
	pthread_t		*philo_thread;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	data_t			data;
}				philo_t;

double  get_time();
long    get_time_ms();
long    atol(const char *s);

#endif
