/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:53:56 by lwyss             #+#    #+#             */
/*   Updated: 2021/10/25 15:51:12 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	tmp[1000000];

	if (n >= 128 * 1024 * 1024)
		return (NULL);
	i = 0;
	if (dest || src)
	{
		while (i < n)
		{
			*(tmp + i) = *(char *)(src + i);
			i++;
		}
		i = 0;
		while (i < n)
		{
			*(char *)(dest + i) = *(tmp + i);
			i++;
		}		
	}
	return (dest);
}
