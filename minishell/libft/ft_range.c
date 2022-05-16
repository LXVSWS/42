/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:55:04 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/14 14:55:40 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_range(int min, int max)
{
	int	*str;
	int	i;

	str = NULL;
	if (min >= max)
		return (str);
	i = 0;
	str = malloc((max - min) * sizeof(int));
	while (min < max)
	{
		str[i] = min;
		min++;
		i++;
	}
	return (str);
}
