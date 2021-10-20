#include "libft/libft.h"

static int	intlen(int a)
{
	int	i;
	int neg;

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

char	*ft_itoa(int n)
{
	char *s = malloc(sizeof(char) * . + 1);
}
