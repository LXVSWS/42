/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:24:40 by lwyss             #+#    #+#             */
/*   Updated: 2021/10/28 19:41:31 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*c1;
	const unsigned char	*c2;

	if (!n)
		return (0);
	c1 = s1;
	c2 = s2;
	i = 0;
	while (i < n && c1[i] == c2[i])
		i++;
	if (i == n)
		return (0);
	return (c1[i] - c2[i]);
}
