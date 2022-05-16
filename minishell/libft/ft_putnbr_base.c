/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:54:18 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/14 15:04:52 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putbase(long nb, char *base)
{
	write(1, &base[nb % ft_strlen(base)], 1);
}

int	check_base(char *str)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			return (0);
		i++;
	}
	i = 0;
	while (str[i])
	{
		tmp = str[i];
		j = i + 1;
		while (str[j])
		{
			if (tmp == str[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_putnbr_base(int nbr, char *base)
{
	int		i;
	long	nb;

	i = 0;
	nb = nbr;
	if (ft_strlen(base) >= 2)
	{
		i = check_base(base);
		if (i == 1)
		{
			if (nb < 0)
			{
				write(1, "-", 1);
				nb *= -1;
			}
			if (nb > (long)ft_strlen(base))
				ft_putnbr_base(nb / ft_strlen(base), base);
			ft_putbase(nb, base);
		}
	}
}
