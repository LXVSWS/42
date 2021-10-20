/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:43:02 by lwyss             #+#    #+#             */
/*   Updated: 2021/10/18 16:43:07 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcat(char *dst, char *src)
{
	int	i;
	int	j;

	i = ft_strlen(dst);
	j = 0;
	while (src[j])
		dst[i++] = src[j++];
	dst[i] = 0;
}

static void	ft_strncat(char *dst, char *src, int size)
{
	int	i;
	int	j;

	i = ft_strlen(dst);
	j = 0;
	while (src[j] && j < size)
		dst[i++] = src[j++];
	dst[i] = 0;
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;

	if (size > ft_strlen(dst) + ft_strlen(src) + 1)
	{
		ft_strcat(dst, (char *)src);
		return (ft_strlen(dst));
	}
	else if (size >= ft_strlen(dst) + 1)
	{
		len = ft_strlen(dst);
		ft_strncat(dst, (char *)src, size - ft_strlen(dst) - 1);
		return (ft_strlen(src) + len);
	}
	return (ft_strlen(src) + size);
}
