/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 12:12:29 by rahmed            #+#    #+#             */
/*   Updated: 2022/02/09 20:47:23 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_add_line_tab(char **tab, char *line)
{
	char	**tab_cpy;
	int		i;

	i = 0;
	if (!line)
		return (tab);
	tab_cpy = ft_calloc(ft_tab_len(tab) + 3, sizeof(char *));
	while (tab[i])
	{
		tab_cpy[i] = ft_strdup(tab[i]);
		i++;
	}
	ft_free_tab(tab);
	tab_cpy[i++] = ft_strdup(line);
	tab_cpy[i] = NULL;
	return (tab_cpy);
}

char	**ft_copy_tab(char **tab)
{
	char	**tab_cpy;
	int		i;

	i = 0;
	tab_cpy = ft_calloc(ft_tab_len(tab) + 2, sizeof(char *));
	while (tab[i])
	{
		tab_cpy[i] = ft_strdup(tab[i]);
		i++;
	}
	tab_cpy[i] = NULL;
	return (tab_cpy);
}

int	ft_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}
