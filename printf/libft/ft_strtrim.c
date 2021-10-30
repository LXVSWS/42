/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:20:21 by lwyss             #+#    #+#             */
/*   Updated: 2021/10/25 18:03:19 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	isep(char char_of_s1, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (char_of_s1 == charset[i++])
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len;
	char	*s;

	i = 0;
	j = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	while (isep(s1[i], (char *)set))
		i++;
	if (i == len)
		return (ft_calloc(1, 1));
	while (isep(s1[--len], (char *)set))
		j++;
	len = ft_strlen(s1) - (i + j);
	s = malloc(sizeof(char) * len + 1);
	if (!s)
		return (NULL);
	s[len] = 0;
	j = 0;
	while (j < len)
		s[j++] = s1[i++];
	return (s);
}
