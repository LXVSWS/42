#include "philo.h"

void    *thinking(void *arg)
{
    struct timeval  time;

    gettimeofday(&time, NULL);
    printf("\033[44m%i %s Thinking\033[0m\n", time.tv_usec, (char *)arg);
    pthread_exit(arg);
}

void    *eating(void *arg)
{
    struct timeval  time;

    gettimeofday(&time, NULL);
    printf("\033[43m%i %s Eating\033[0m\n", time.tv_usec, (char *)arg);
    pthread_exit(arg);
}

int main()
{
    pthread_t       p1;
    pthread_t       p2;
    struct timeval  time;
    
    gettimeofday(&time, NULL);
    printf("\033[42m%i Starting\033[0m\n", time.tv_usec);
    pthread_create(&p1, NULL, thinking, "1");
    pthread_create(&p2, NULL, eating, "2");
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    return (0);
}

// printf("\033[...m------\033[0m\n"); ... = 41 -> 47 & 89 -> 97