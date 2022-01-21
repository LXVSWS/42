/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 19:50:51 by lwyss             #+#    #+#             */
/*   Updated: 2022/01/21 20:36:02 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	small_sort(t_list **list_a, t_list **list_b, int size)
{
	(void)size;
	pb(list_a, list_b);
	pa(list_a, list_b);
	ra(list_a);
	rra(list_a, size);
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
