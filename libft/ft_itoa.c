/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:24:13 by lwyss             #+#    #+#             */
/*   Updated: 2021/10/20 14:24:18 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intlen(int a)
{
	int	i;
	int	neg;

	i = 0;
	neg = 0;
	if (a <= 0)
	{
		neg = 1;
		a *= -1;
	}
	while (a > 0)
	{
		a /= 10;
		i++;
	}
	return (i + neg);
}

char	*ft_itoa(int n)
{
	int		len;
	int		neg;
	char	*s;

	if (n <= -2147483648)
		return (ft_strdup("-2147483648"));
	neg = 0;
	len = intlen(n);
	s = malloc(sizeof(char) * len + 1);
	if (!s)
		return (NULL);
	s[len] = 0;
	if (n < 0)
	{
		s[0] = '-';
		n *= -1;
		neg = 1;
	}
	while (len-- > 0 + neg)
	{
		s[len] = n % 10 + 48;
		n /= 10;
	}
	return (s);
}
