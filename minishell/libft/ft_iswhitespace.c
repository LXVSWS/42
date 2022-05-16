/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 15:55:56 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/08 17:46:37 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_iswhitespace(int c)
{
	if ((c == ' ') || (c == '\t') || (c == '\n') || \
	(c == '\r') || (c == '\v') || (c == '\f'))
		return (1);
	return (0);
}

int	ft_is_str_blank(char *str)
{
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (!ft_iswhitespace(*str))
			return (0);
		str++;
	}
	return (1);
}

void	skip_whitespace(char **line)
{
	while (ft_iswhitespace(**line))
		(*line)++;
}

void	skip_blank(char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
}
