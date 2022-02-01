#ifndef PHILO__H
# define PHILO__H

typedef struct  data
{
    int         philo_total;
    int         time_to_die;
    int         time_to_eat;
    int         time_to_sleep;
    int         meals_needed;
}               data;

long    atol(const char *s);

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

#endif