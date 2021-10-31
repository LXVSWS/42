#include "libft/libft.h"
#include <stdarg.h>
#include <stdio.h>

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	char	*str;
	int		i;

	va_start(ap, s);
	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	str = va_arg(ap, char *);
	write(1, str, ft_strlen(str));
	va_end(ap);
	return (i);
}

int	main(int ac, char **av)
{
	(void)ac;
	ft_putnbr_fd(ft_printf("my printf : %s", av[1]), 1);
	ft_putnbr_fd(printf("\noriginal printf : %s", av[1]), 1);
}
