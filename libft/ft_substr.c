/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:55:05 by lwyss             #+#    #+#             */
/*   Updated: 2021/10/18 16:55:09 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	str = malloc(sizeof(char) * len);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
		str[i++] = s[start++];
	str[i] = 0;
	return (str);
}
