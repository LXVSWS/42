/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 11:37:05 by rahmed            #+#    #+#             */
/*   Updated: 2021/11/18 16:47:56 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	start_len(char const *s1, char const *set)
{
	size_t	i_s1;
	size_t	i_set;
	size_t	occur;

	i_s1 = 0;
	while (i_s1 < ft_strlen(s1))
	{
		i_set = 0;
		occur = 0;
		while (i_set < ft_strlen(set))
			if (s1[i_s1] == set[i_set++])
				occur++;
		if (!occur)
			return (i_s1);
		i_s1++;
	}
	return (i_s1);
}

static size_t	end_len(char const *s1, char const *set)
{
	size_t	i_s1;
	size_t	i_set;
	size_t	occur;
	size_t	end_s1;

	end_s1 = ft_strlen(s1) - 1;
	i_s1 = 0;
	while ((end_s1 - i_s1) > 0)
	{
		i_set = 0;
		occur = 0;
		while (i_set < ft_strlen(set))
			if (s1[end_s1 - i_s1] == set[i_set++])
				occur++;
		if (!occur)
			return (i_s1);
		i_s1++;
	}
	return (i_s1);
}

static size_t	str_trim_len(char const *s1, char const *set)
{
	if (ft_strlen(s1) > start_len(s1, set) + end_len(s1, set))
		return (ft_strlen(s1) - start_len(s1, set) - end_len(s1, set));
	else
		return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i_s1;
	size_t	i_str;

	if (!s1 || !set)
		return (NULL);
	i_s1 = start_len(s1, set);
	i_str = 0;
	str = ft_calloc((str_trim_len(s1, set) + 1), sizeof(*str));
	if (!str)
		return (NULL);
	while (i_str < str_trim_len(s1, set))
		str[i_str++] = s1[i_s1++];
	str[i_str] = '\0';
	return (str);
}
