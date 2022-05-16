/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex_nbchr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:59:03 by rahmed            #+#    #+#             */
/*   Updated: 2021/11/14 16:58:12 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_hex_nbchr(unsigned long nbr, int capitalize, int *nbchr)
{
	char	*base;

	if (capitalize)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (nbr >= 16)
	{
		ft_putnbr_hex_nbchr(nbr / 16, capitalize, nbchr);
		ft_putchar_nbchr(base[nbr % 16], nbchr);
	}
	else
		ft_putchar_nbchr(base[nbr], nbchr);
}
