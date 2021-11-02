#include "libft/libft.h"
#include "printf.h"

static void	hex(long n, int	*size)
{
    int	c;

    if (n >= 16)
        hex(n / 16, size);
    c = n % 16 + (n % 16 < 10 ? '0' : 'a' - 10);
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
			size += write(1, str, ft_strlen(str));
			i++;
		}
		else if (s[i] == '%' && (s[i + 1] == 'i' || s[i + 1] == 'd'))
		{
			intg = va_arg(ap, int);
			size += write(1, ft_itoa(intg), ft_strlen(ft_itoa(intg)));
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
			size += write(1, ft_itoa(ui), ft_strlen(ft_itoa(ui)));
			i++;
		}
		else if (s[i] == '%' && s[i + 1] == 'x')
		{
			intg = va_arg(ap, int);
			hex(intg, &size);
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
