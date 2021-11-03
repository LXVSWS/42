/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 23:15:07 by lwyss             #+#    #+#             */
/*   Updated: 2021/11/04 00:36:26 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	va_list			ap;
	int				i;
	int				size;

	va_start(ap, s);
	i = 0;
	size = 0;
	while (s[i])
	{
		if (s[i] == '%')
			size += ft_getflag(s[++i], ap);
		else
			size += write(1, &s[i], 1);
		i++;
	}
	va_end(ap);
	return (size);
}
