/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:49:44 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/14 14:49:52 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_index_base(int nb, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == nb)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(const char *str, char *base)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	if (!ft_check_base(base))
		return (write(2, "Base Error\n", 1));
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i])
	{
		res *= ft_strlen(base);
		res += ft_index_base(str[i], base);
		i++;
	}
	return (res);
}
