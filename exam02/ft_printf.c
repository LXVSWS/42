#include <unistd.h>
#include <stdarg.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	print_s(char *s)
{
	if (s)
		return (write(1, s, ft_strlen(s)));
	return (write(1, "(null)", 6));
}

int	putnbr(int nb)
{
	static int size = 0;

	if (nb == -2147483648)
	{
		write(1, "-2147483648", ft_strlen("-2147483648"));
		return (ft_strlen("-2147483648"));
	}
	if (nb < 0 && nb >= -2147483647)
	{
		size += write(1, "-", 1);
		nb *= -1;
	}
	if (nb > 9)
		putnbr(nb / 10);
	size += write(1, &"0123456789"[nb % 10], 1);
	return (size);
}


void	puthex(unsigned long long nb)
{
	char *base = "0123456789abcdef";

	if (nb >= 16)
		puthex(nb / 16);
	write(1, &base[nb % 16], 1);
}

int	putsize(unsigned long long nb)
{
	int	size = 0;

	puthex(nb);
	if (nb == 0)
		return (1);
	while (nb)
	{
		nb /= 16;
		size++;
	}
	return (size);
}

int	getflag(char c, va_list ap)
{
	int	size = 0;

	if (c == 's')
		return (print_s(va_arg(ap, char *)));
	else if (c == 'd')
		return (putnbr(va_arg(ap, int)));
	else if (c == 'x')
		return (putsize(va_arg(ap, unsigned int)));
	else
		return (write(1, "%", 1));
	return (size);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		i = 0;
	int		size = 0;

	va_start(ap, s);
	while (s[i])
	{
		if (s[i] == '%')
			size += getflag(s[++i], ap);
		else
			size += write(1, &s[i], 1);
		i++;
	}
	va_end(ap);
	return (size);
}
