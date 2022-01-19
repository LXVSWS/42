/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:24:42 by lwyss             #+#    #+#             */
/*   Updated: 2022/01/19 17:21:27 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

t_list	*pb(t_list *list_a, t_list **list_b)
{
	t_list	*tmp;

	tmp = list_a;
	if (list_a)
	{
		tmp = list_a->next;
		ft_lstadd_front(list_b, list_a);
	}
	write(1, "pb\n", 3);
	return (tmp);
}

t_list	*pa(t_list **list_a, t_list *list_b)
{
	t_list	*tmp;

	tmp = list_b;
	if (list_b)
	{
		tmp = list_b->next;
		ft_lstadd_front(list_a, list_b);
	}
	write(1, "pa\n", 3);
	return (tmp);
}

void	ra(t_list **list_a)
{
	t_list	*tmp;
	t_list	*last;

	if ((*list_a)->next)
	{
		tmp = (*list_a)->next;
		last = ft_lstlast(*list_a);
		(*list_a)->next = NULL;
		last->next = *list_a;
		*list_a = tmp;
	}
	write(1, "ra\n", 3);
}

void	print_lists(t_list *list_a, t_list *list_b)
{
	while (list_a)
	{
		printf("A : %i\n", *(list_a->content));
		list_a = list_a->next;
	}
	while (list_b)
	{
		printf("B : %i\n", *(list_b->content));
		list_b = list_b->next;
	}
}
