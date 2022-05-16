/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:04:13 by rahmed            #+#    #+#             */
/*   Updated: 2021/11/18 16:51:41 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	put_vars(const char *format, va_list param, int *nbchr)
{
	if (*format == 'c')
		ft_putchar_nbchr(va_arg(param, int), nbchr);
	else if (*format == 's')
		ft_putstr_nbchr(va_arg(param, char *), nbchr);
	else if ((*format == 'd') || (*format == 'i'))
		ft_putnbr_nbchr(va_arg(param, int), nbchr);
	else if (*format == 'u')
		ft_putnbr_nbchr(va_arg(param, unsigned int), nbchr);
	else if (*format == 'p')
	{
		ft_putstr_nbchr("0x", nbchr);
		ft_putnbr_hex_nbchr(va_arg(param, unsigned long), 0, nbchr);
	}
	else if (*format == 'x')
		ft_putnbr_hex_nbchr(va_arg(param, unsigned int), 0, nbchr);
	else if (*format == 'X')
		ft_putnbr_hex_nbchr(va_arg(param, unsigned int), 1, nbchr);
	else if (*format == '%')
		ft_putchar_nbchr('%', nbchr);
}

int	ft_printf(const char *format, ...)
{
	va_list	param;
	int		nbchr;
	int		i;

	nbchr = 0;
	i = 0;
	va_start(param, format);
	while (format[i])
	{
		if ((format[i] == '%') && (format[i + 1]))
			put_vars(&(format[++i]), param, &nbchr);
		else
			ft_putchar_nbchr(format[i], &nbchr);
		i++;
	}
	va_end(param);
	return (nbchr);
}
