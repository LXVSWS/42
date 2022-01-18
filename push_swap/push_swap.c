/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:18:31 by lwyss             #+#    #+#             */
/*   Updated: 2022/01/18 19:33:16 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	**create_setint(int size, char **set)
{
	int	**a;
	int	*d;
	int	i;

	a = malloc(sizeof(int *) * size + 1);
	a[size] = NULL;
	i = -1;
	while (set[++i])
	{
		d = malloc(sizeof(int));
		*d = (int)ft_atol(set[i]);
		a[i] = d;
	}
	i = -1;
	while (set[++i])
		free(set[i]);
	free(set);
	return (a);
}

static void	clean_exit(void **set)
{
	int	i;

	write(2, "Error\n", 6);
	i = -1;
	while (set[++i])
		free(set[i]);
	free(set);
	exit(1);
}

static int	**parsing(char **set)
{
	int		i;
	int		y;

	i = -1;
	y = -1;
	while (set[++i])
	{
		while (set[i][++y])
			if ((set[i][y] < 48 || set[i][y] > 57) && set[i][y] != 45)
				clean_exit((void **)set);
		y = -1;
		if (ft_atol(set[i]) < -2147483648 || ft_atol(set[i]) > 2147483647)
			clean_exit((void **)set);
	}
	return (create_setint(i, set));
}

int	main(int ac, char **av)
{
	int		**a;
	int		i;
	int		y;
	t_list	*list_a;
	t_list	*list_b;

	if (ac == 2)
	{
		a = parsing(ft_split(av[1], ' '));
		i = -1;
		while (a[++i])
		{
			y = i;
			while (a[++y])
				if (*a[y] == *a[i])
					clean_exit((void **)a);
			ft_lstadd_back(&list_a, ft_lstnew(a[i]));
		}
		list_b = NULL;
		list_a = pb(list_a, &list_b);
		list_b = pa(&list_a, list_b);
		ra(&list_a);
		print_lists(list_a, list_b);
	}
}
