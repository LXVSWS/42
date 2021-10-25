/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:53:30 by lwyss             #+#    #+#             */
/*   Updated: 2021/10/25 15:53:39 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	while (n > i)
	{
		c1 = (unsigned char)s1[i];
		c2 = (unsigned char)s2[i];
		if ((c1 != c2) || c1 == 0 || c2 == 0)
			return (c1 - c2);
		i++;
	}
	return (c1 - c2);
}
