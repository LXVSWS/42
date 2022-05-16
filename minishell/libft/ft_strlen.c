/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 19:32:08 by rahmed            #+#    #+#             */
/*   Updated: 2022/04/15 00:45:54 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

size_t	ft_strlen_no_sp(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len] && !ft_iswhitespace(s[len]))
		len++;
	return (len);
}
