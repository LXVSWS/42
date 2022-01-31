/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:11:44 by lwyss             #+#    #+#             */
/*   Updated: 2022/01/31 15:08:54 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_list(t_list **list)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *list;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}

int	**stock(t_list **list_a, int size)
{
	t_list	*tmp;
	int		**or;
	int		i;

	or = malloc(sizeof(int *) * size);
	tmp = *list_a;
	i = 0;
	while (tmp)
	{
		or[i++] = tmp->content;
		tmp = tmp->next;
	}
	return (or);
}

void	simplify(t_list **list_a, int size)
{
	t_list	*tmp;
	int		**or;
	int		i;

	or = stock(list_a, size);
	bubble_sort(list_a);
	tmp = *list_a;
	i = 0;
	while (tmp)
	{
		*(tmp->content) = i++;
		tmp = tmp->next;
	}
	tmp = *list_a;
	i = 0;
	while (tmp)
	{
		tmp->content = or[i++];
		tmp = tmp->next;
	}
	free(or);
}

static void	subfunction(t_list **list_a, t_list **list_b, int **val)
{
	t_list	*tmp;

	tmp = *list_a;
	while (tmp->content != val[0] && tmp->content != val[1] \
	&& tmp->content != val[2])
	{
		ra(list_a);
		tmp = *list_a;
	}
	pb(list_a, list_b);
}

void	final_sort(t_list **list_a, t_list **list_b, int **val)
{
	t_list	*tmp;

	subfunction(list_a, list_b, val);
	subfunction(list_a, list_b, val);
	small_sort(list_a, 3);
	pa(list_a, list_b);
	pa(list_a, list_b);
	tmp = *list_a;
	while (test_sort(list_a))
	{
		if (tmp->content == val[2])
			ra(list_a);
		if (tmp->content == val[1])
			sa(list_a);
		if (tmp->content == val[0] && tmp->next->content == val[2])
		{
			sa(list_a);
			ra(list_a);
		}
		tmp = *list_a;
	}
}
