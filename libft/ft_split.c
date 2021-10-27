/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 00:31:30 by lwyss             #+#    #+#             */
/*   Updated: 2021/10/28 01:15:01 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isep(char c1, char c2)
{
	if (c1 == c2)
		return (1);
	return (0);
}

static int	countword(char *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			word++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (word);
}

static int	sizeword(char *s, char sep)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != sep)
		i++;
	return (i);
}

static char	*wordalloc(int size)
{
	char	*word;

	word = malloc(sizeof(char) * size + 1);
	if (!word)
		return (NULL);
	word[size] = 0;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**pp;
	int		wsize;
	int		os;
	int		i;
	int		j;

	pp = malloc(sizeof(char *) * (countword((char *)s, c) + 1));
	if (!s || !pp)
		return (NULL);
	os = 0;
	i = -1;
	while (++i < countword((char *)s, c))
	{
		while (isep(s[os], c))
			os++;
		wsize = sizeword((char *)&s[os], c);
		pp[i] = wordalloc(wsize);
		j = 0;
		while (j < wsize)
			pp[i][j++] = s[os++];
		pp[i][j] = 0;
	}
	*(pp + i) = NULL;
	return (pp);
}
