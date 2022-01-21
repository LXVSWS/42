/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 19:50:51 by lwyss             #+#    #+#             */
/*   Updated: 2022/01/21 21:39:56 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	small_sort(t_list **list_a, t_list **list_b, int size)
{
	t_list	*tmp;

	(void)size;
	tmp = *list_a;
	if (*(tmp->content) > *(tmp->next->content))
		sa(list_a);
	rra(list_a, size);
	pb(list_a, list_b);
	pa(list_a, list_b);
	ra(list_a);
	print_lists(*list_a, *list_b);
	exit(0);
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
