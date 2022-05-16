/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:58:09 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/14 14:58:12 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr_out(const char *str, const char *tofind, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (tofind[i] == 0)
		return ((char *)str);
	while (str[i] && i < n)
	{
		if (str[i] == tofind[j])
		{
			while (str[i + j] == tofind[j] && i + j < n)
			{
				if (tofind[j + 1] == '\0' )
					return ((char *)str + i + j + 1);
				j++;
			}
		}
		j = 0;
		i++;
	}
	return (0);
}
