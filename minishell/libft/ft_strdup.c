/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 20:05:19 by rahmed            #+#    #+#             */
/*   Updated: 2021/11/18 16:47:56 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*tab;
	int		i;
	int		lensrc;

	i = 0;
	lensrc = ft_strlen(s1);
	tab = (char *)ft_calloc((lensrc + 1), sizeof(*tab));
	if (!tab)
		return (NULL);
	while (i < lensrc)
	{
		tab[i] = s1[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
