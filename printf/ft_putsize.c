/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 23:28:17 by lwyss             #+#    #+#             */
/*   Updated: 2021/11/03 23:28:54 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

static void	putbase(unsigned long long nb, char *base)
{
	if (nb >= ft_strlen(base))
		putbase(nb / ft_strlen(base), base);
	ft_putchar_fd(base[nb % ft_strlen(base)], 1);
}

int	putsize(unsigned long long i, char *base, void *ptr)
{
	int	size;

	if (ptr)
		i = (unsigned long long)ptr;
	size = 0;
	putbase(i, base);
	if (i == 0)
		return (1);
	while (i)
	{
		i /= ft_strlen(base);
		size++;
	}
	return (size);
}
