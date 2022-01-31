/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:53:36 by lwyss             #+#    #+#             */
/*   Updated: 2022/01/31 14:55:27 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	**parsing_multiple_args(char **av)
{
	char	str[1000000];
	int		i;
	int		y;
	int		j;

	i = 0;
	y = -1;
	j = -1;
	while (av[++i])
	{
		while (av[i][++y])
			str[++j] = av[i][y];
		str[++j] = ' ';
		y = -1;
	}
	return (parsing(ft_split(str, ' ')));
}

void	check_double(int **a, int i)
{
	int	y;

	y = i;
	while (a[++y])
		if (*a[y] == *a[i])
			clean_exit((void **)a, 1);
}

void	replace_list(t_list **list_a, int **or)
{
	t_list	*tmp;
	int		i;

	tmp = *list_a;
	i = 0;
	while (tmp)
	{
		tmp->content = or[i++];
		tmp = tmp->next;
	}
}
