#include "minitalk.h"

size_t	strlen(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	intlen(int a)
{
	int	i;
	int	neg;

	i = 0;
	neg = 0;
	if (a <= 0)
	{
		neg = 1;
		a *= -1;
	}
	while (a > 0)
	{
		a /= 10;
		i++;
	}
	return (i + neg);
}

char	*itoa(int n)
{
	int		len;
	int		neg;
	char	*s;

	neg = 0;
	len = intlen(n);
	s = malloc(sizeof(char) * len + 1);
	if (!s)
		return (NULL);
	s[len] = 0;
	if (n < 0)
	{
		s[0] = '-';
		n *= -1;
		neg = 1;
	}
	while (len-- > 0 + neg)
	{
		s[len] = n % 10 + 48;
		n /= 10;
	}
	return (s);
}
