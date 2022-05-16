/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 15:29:17 by rahmed            #+#    #+#             */
/*   Updated: 2022/02/05 17:20:55 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_del_nl(char *str)
{
	int	i;

	i = 0;
	while ((str[i] != '\n') && str[i])
		i++;
	str[i] = '\0';
	return (str);
}

char	*ft_del_at_whitespace(char *str)
{
	int	i;

	i = 0;
	while (!ft_iswhitespace(str[i]) && str[i])
		i++;
	str[i] = '\0';
	return (str);
}
