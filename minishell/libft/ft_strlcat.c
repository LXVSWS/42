/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 21:40:01 by rahmed            #+#    #+#             */
/*   Updated: 2021/11/18 16:47:56 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	isrc;
	unsigned int	lendest;
	unsigned int	lensrc;

	isrc = 0;
	lendest = ft_strlen(dst);
	lensrc = ft_strlen(src);
	if (!dstsize || lendest > dstsize)
		return (lensrc + dstsize);
	while ((src[isrc] != '\0') && (lendest + isrc < dstsize - 1))
	{
		dst[lendest + isrc] = src [isrc];
		isrc++;
	}
	dst[lendest + isrc] = '\0';
	return (lendest + lensrc);
}
