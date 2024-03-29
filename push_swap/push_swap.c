/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:18:31 by lwyss             #+#    #+#             */
/*   Updated: 2022/01/29 17:27:59 by lwyss            ###   ########.fr       */
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

void	clean_exit(void **set, int flag)
{
	int		i;

	if (flag == 0 || flag == 1)
	{
		i = -1;
		while (set[++i])
			free(set[i]);
		free(set);
	}
	if (flag == 1)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
}

int	**parsing(char **set)
{
	int		i;
	int		y;

	i = -1;
	y = -1;
	while (set[++i])
	{
		while (set[i][++y])
		{
			if ((set[i][y] < 48 || set[i][y] > 57) && set[i][y] != 45)
				clean_exit((void **)set, 1);
			if ((set[i][y] == 45 && (set[i][y + 1] < 48 || set[i][y + 1] > 57)))
				clean_exit((void **)set, 1);
			if (((set[i][y] > 48 && set[i][y] < 57) && set[i][y + 1] == 45 && \
			(set[i][y + 2] > 48 || set[i][y + 2] < 57)))
				clean_exit((void **)set, 1);
		}
		y = -1;
		if (ft_atol(set[i]) < -2147483648 || ft_atol(set[i]) > 2147483647)
			clean_exit((void **)set, 1);
	}
	return (create_setint(i, set));
}

static void	sort(t_list	**list_a, t_list **list_b, int size)
{
	t_list	*tmp;

	tmp = *list_a;
	if (size == 1)
		exit(1);
	else if (size == 2)
	{
		if (*(tmp->content) > *(tmp->next->content))
			sa(list_a);
	}
	else if (!test_sort(list_a))
		exit(1);
	else if (size == 3)
		small_sort(list_a, size);
	else if (size == 5)
		medium_sort(list_a, list_b, size);
	else if (size == 4 || size > 5)
	{
		simplify(list_a, size);
		radix_sort(list_a, list_b, size);
	}
}

int	main(int ac, char **av)
{
	int		**a;
	int		i;
	t_list	*list_a;
	t_list	*list_b;

	if (ac > 1)
	{
		if (ac > 2)
			a = parsing_multiple_args(av);
		else
			a = parsing(ft_split(av[1], ' '));
		list_a = NULL;
		list_b = NULL;
		i = -1;
		while (a[++i])
		{
			check_double(a, i);
			ft_lstadd_back(&list_a, ft_lstnew(a[i]));
		}
		sort(&list_a, &list_b, i);
		clean_exit((void **)a, 0);
		free_list(&list_a);
	}
}
