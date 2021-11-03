/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getflag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 23:55:24 by lwyss             #+#    #+#             */
/*   Updated: 2021/11/04 00:02:36 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

int	ft_getflag(char c, va_list ap)
{
	int	size;

	size = 0;
	if (c == 'c')
		return (print_c(va_arg(ap, int)));
	else if (c == 's')
		return (print_s(va_arg(ap, char *)));
	else if (c == 'p')
		return (write(1, "0x", 2) + \
		ft_putsize(0, "0123456789abcdef", (void *)va_arg(ap, char *)));
	else if (c == 'i' || c == 'd')
		return (print_id(va_arg(ap, int)));
	else if (c == 'u')
		return (ft_putsize(va_arg(ap, unsigned int), "0123456789", NULL));
	else if (c == 'x')
		return (ft_putsize(va_arg(ap, unsigned int), "0123456789abcdef", NULL));
	else if (c == 'X')
		return (ft_putsize(va_arg(ap, unsigned int), "0123456789ABCDEF", NULL));
	else if (c == '%')
		return (write(1, "%", 1));
	return (0);
}
