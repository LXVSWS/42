/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:46:26 by lwyss             #+#    #+#             */
/*   Updated: 2021/10/18 15:46:35 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;

	ptr = malloc(nmemb * size);
	i = 0;
	if (nmemb == 0 || size == 0)
		return (NULL);
	if (!(ptr))
		return (NULL);
	while (i < nmemb * size)
		*(char *)(ptr + i++) = 0;
	return (ptr);
}
