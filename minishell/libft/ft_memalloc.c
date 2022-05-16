/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:52:51 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/14 14:52:51 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*pt;
	size_t	i;

	i = 0;
	pt = malloc(sizeof(size));
	while (i < size)
		((unsigned char *)pt)[i++] = 0;
	return (pt);
}
