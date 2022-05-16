/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_nbchr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:00:06 by rahmed            #+#    #+#             */
/*   Updated: 2021/11/14 16:58:14 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_nbchr(long nbr, int *nbchr)
{
	char	*base;

	base = "0123456789";
	if (nbr < 0)
	{
		ft_putchar_nbchr('-', nbchr);
		nbr *= -1;
	}
	if (nbr >= 10)
	{
		ft_putnbr_nbchr(nbr / 10, nbchr);
		ft_putchar_nbchr(base[nbr % 10], nbchr);
	}
	else
		ft_putchar_nbchr(base[nbr], nbchr);
}
