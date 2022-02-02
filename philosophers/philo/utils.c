#include "philo.h"

double	get_time()
{
    struct timeval	time;

    gettimeofday(&time, NULL);
	return (time.tv_sec + (time.tv_usec * 0.000001));
	return (0);
}

long	get_time_ms()
{
    struct timeval	time;

    gettimeofday(&time, NULL);
	return ((time.tv_sec + (time.tv_usec * 0.000001)) * 1000);
}

long	atol(const char *s)
{
	int			i;
	int			neg;
	long		res;

	i = 0;
	neg = 0;
	res = 0;
	while (s[i] == '\v' || s[i] == '\n' || s[i] == '\t' \
	|| s[i] == '\r' || s[i] == '\f' || s[i] == ' ')
		i++;
	if (s[i] == '-' && (s[i + 1] >= '0' && s[i] <= '9'))
	{
		neg++;
		i++;
	}
	if (s[i] == '+' && (s[i + 1] >= '0' && s[i] <= '9'))
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res *= 10;
		res += (s[i++] - 48);
	}
	if (neg == 1)
		return (-res);
	return (res);
}
