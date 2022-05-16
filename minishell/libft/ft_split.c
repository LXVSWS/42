/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 14:51:18 by rahmed            #+#    #+#             */
/*   Updated: 2021/12/31 01:01:46 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcount(char const *s, char sep)
{
	size_t	i;
	size_t	check;
	int		nbstr;

	i = 0;
	check = 0;
	nbstr = 0;
	if (!s)
		return (0);
	while ((s[i] == sep) && s[i])
		i++;
	while (s[i])
	{
		check++;
		if ((s[i] == sep) && (s[i - 1] != sep))
			++nbstr;
		else if ((s[i] != sep) && (s[i + 1] == '\0'))
			++nbstr;
		i++;
	}
	if (!nbstr && check)
		return (1);
	return (nbstr);
}

static char	**ft_unalloc(char **tab, size_t n)
{
	size_t	i;

	i = 0;
	while (i <= n)
	{
		if (tab[i] != NULL)
			free(tab[i]);
		tab[i++] = NULL;
	}
	if (tab != NULL)
		free(tab);
	tab = NULL;
	return (tab);
}

static char	**ft_taballoc(char const *s, char c)
{
	size_t	i_str;
	size_t	i_s;
	size_t	offset;
	size_t	nbstr;
	char	**tab;

	i_str = 0;
	i_s = 0;
	nbstr = ft_strcount(s, c);
	tab = ft_calloc((nbstr + 1), sizeof(*tab));
	if (!tab)
		return (ft_unalloc(tab, i_str));
	while ((i_str < nbstr) && s[i_s])
	{
		offset = i_s;
		while ((s[i_s] != c) && s[i_s])
			i_s++;
		tab[i_str] = ft_calloc((i_s - offset + 1), sizeof(tab));
		if (!tab[i_str])
			return (ft_unalloc(tab, i_str));
		i_str++;
		i_s++;
	}
	tab[i_str] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	i_str;
	size_t	i_s;
	size_t	nbstr;
	char	**tab;

	i_s = 0;
	i_str = 0;
	if (!s)
		return (NULL);
	tab = ft_taballoc(s, c);
	if (!tab)
		return (ft_unalloc(tab, i_str));
	nbstr = ft_strcount(s, c);
	while ((i_str < nbstr) && s[i_s])
	{
		i = 0;
		while ((s[i_s] != c) && (s[i_s] != '\0'))
			tab[i_str][i++] = s[i_s++];
		if (i)
			tab[i_str++][i] = '\0';
		i_s++;
	}
	tab[i_str] = NULL;
	return (tab);
}
