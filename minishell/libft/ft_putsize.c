/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:54:42 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/14 14:54:45 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putbase(unsigned long long nb, char *str)
{
	if (nb >= ft_strlen(str))
		ft_putbase(nb / ft_strlen(str), str);
	ft_putchar(str[nb % ft_strlen(str)]);
}

int	ft_putsize(unsigned long long nb, char *base)
{
	int	i;

	i = 0;
	ft_putbase(nb, base);
	while (nb != 0)
	{
		nb /= ft_strlen(base);
		i++;
	}
	return (i);
}
