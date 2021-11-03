/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 23:48:13 by lwyss             #+#    #+#             */
/*   Updated: 2021/11/03 23:49:06 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

int	print_c(char c)
{
	return (write(1, &c, 1));
}

int	print_s(char *s)
{
	if (s)
		return (write(1, s, ft_strlen(s)));
	return (write(1, "(null)", 6));
}

int	print_id(int i)
{
	int		size;
	char	*s;

	size = 0;
	s = ft_itoa(i);
	size = write(1, s, ft_strlen(s));
	free(s);
	return (size);
}
