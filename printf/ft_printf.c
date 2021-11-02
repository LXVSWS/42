#include "libft/libft.h"
#include "ft_printf.h"

static void	hex(long n, int	*size)
{
    int	c;

    if (n >= 16)
        hex(n / 16, size);
    c = n % 16 + (n % 16 < 10 ? '0' : 'a' - 10);
    ft_putchar_fd(c, 1);
	(*size)++;
}

static void	hexmaj(long n, int *size)
{
    int	c;

    if (n >= 16)
        hex(n / 16, size);
    c = n % 16 + (n % 16 < 10 ? '0' : 'A' - 10);
    ft_putchar_fd(c, 1);
	(*size)++;
}

int	ft_printf(const char *s, ...)
{
	va_list			ap;
	int				i;
	int				size;
	char			*str;
	int				intg;
	char			c;
	unsigned int	ui;

	va_start(ap, s);
	i = 0;
	size = 0;
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1] == 's')
		{
			str = va_arg(ap, char *);
			if (str)
				size += write(1, str, ft_strlen(str));
			else
				size += write(1, "(null)", 6);
			i++;
		}
		else if (s[i] == '%' && (s[i + 1] == 'i' || s[i + 1] == 'd'))
		{
			intg = va_arg(ap, int);
			str = ft_itoa(intg);
			size += write(1, str, ft_strlen(str));
			free(str);
			i++;
		}
		else if (s[i] == '%' && s[i + 1] == 'c')
		{
			c = va_arg(ap, int);
			size += write(1, &c, 1);
			i++;
		}
		else if (s[i] == '%' && s[i + 1] == 'u')
		{
			ui = va_arg(ap, unsigned int);
			str = ft_itoa(ui);
			size += write(1, str, ft_strlen(str));
			free(str);
			i++;
		}
		else if (s[i] == '%' && s[i + 1] == 'x')
		{
			intg = va_arg(ap, int);
			hex(intg, &size);
			i++;
		}
		else if (s[i] == '%' && s[i + 1] == 'X')
		{
			intg = va_arg(ap, int);
			hexmaj(intg, &size);
			i++;
		}
		else if (s[i] == '%' && s[i + 1] == 'p')
		{
			size += write(1, "0x", 2);
			intg = va_arg(ap, int);
			hex(intg, &size);
			i++;
		}
		else if (s[i] == '%' && s[i + 1] == '%')
		{
			size += write(1, "%", 1);
			i++;
		}
		else
			size += write(1, &s[i], 1);
		i++;
	}
	va_end(ap);
	return (size);
}

/*
uintptr_t

while (str[i])
{
	if (str[i] == '%')
		get(str[++i])
	else
		write(1, &str[i], 1)
}

get(char c)
{
	if (c == 'c')
		print_c()
	else if (c == 's')
		print_s()
}
*/
