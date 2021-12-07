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

void	putnbr(long long int nb)
{
	if (nb == -2147483648)
		write(1, "-2147483648", ft_strlen("-2147483648"));
	if (nb < 0 && nb >= -2147483647)
	{
		write(1, "-", 1);
		nb *= -1;
	}
	if (nb >= 10)
		putnbr(nb / 10);
	write(1, &"0123456789"[nb % 10], 1);
}

int	putsize_nbr(long long int nb)
{
	int	size = 0;

	putnbr(nb);
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb *= -1;
		size++;
	}
	while (nb)
	{
		nb /= 10;
		size++;
	}
	return (size);
}

void	puthex(unsigned long long nb)
{
	if (nb >= 16)
		puthex(nb / 16);
	write(1, &"0123456789abcdef"[nb % 16], 1);
}

int	putsize_hex(unsigned long long nb)
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
		return (putsize_nbr(va_arg(ap, int)));
	else if (c == 'x')
		return (putsize_hex(va_arg(ap, unsigned int)));
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
