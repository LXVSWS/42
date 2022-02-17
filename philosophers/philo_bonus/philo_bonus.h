#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>

typedef struct data
{
	int				philo_total;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_needed;
	long			start_time;
	int				dead;
}	t_data;

typedef struct philo
{
	int				number;
	double			last_meal;
	t_data			*data;
}	t_philo;

double	get_time(void);
long	get_time_ms(void);
long	atol(const char *s);

#endif
