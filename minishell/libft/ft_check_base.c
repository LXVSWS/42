/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:50:30 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/14 14:50:30 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_base(char *str)
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

int	ft_check_base(char *base)
{
	if (ft_strlen(base) > 1 && check_base(base))
		return (1);
	return (0);
}
