/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:11:19 by lwyss             #+#    #+#             */
/*   Updated: 2022/01/11 19:41:21 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	ft_strlen(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_atoi(const char *s)
{
	int	i;
	int	neg;
	int	res;

	i = 0;
	neg = 0;
	res = 0;
	while (s[i] == '\v' || s[i] == '\n' || s[i] == '\t' \
	|| s[i] == '\r' || s[i] == '\f' || s[i] == ' ')
		i++;
	if (s[i] == '-' && (s[i + 1] >= '0' && s[i] <= '9'))
	{
		neg++;
		i++;
	}
	if (s[i] == '+' && (s[i + 1] >= '0' && s[i] <= '9'))
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res *= 10;
		res += (s[i++] - 48);
	}
	if (neg == 1)
		return (-res);
	return (res);
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

static char	**wordcopy(char **pp, char *s, char c)
{
	int		os;
	int		i;
	int		j;
	int		wsize;

	os = 0;
	i = -1;
	while (++i < countword((char *)s, c))
	{
		while (s[os] == c)
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

char	**ft_split(char const *s, char c)
{
	char	**pp;

	if (!s)
		return (NULL);
	pp = malloc(sizeof(char *) * (countword((char *)s, c) + 1));
	if (!pp)
		return (NULL);
	pp = wordcopy(pp, (char *)s, c);
	return (pp);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*l;

	l = malloc(sizeof(t_list));
	if (!l)
		return (NULL);
	l->content = content;
	l->next = NULL;
	return (l);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*tmp;

	tmp = *alst;
	if (*alst)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*alst = new;
}
