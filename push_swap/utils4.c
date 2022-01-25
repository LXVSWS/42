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

int	test_sort(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp->next)
		if (*(tmp->content) < *(tmp->next->content))
			tmp = tmp->next;
		else
			return (1);
	return (0);
}

void	small_sort(t_list **list_a, int size)
{
	t_list	*tmp;
	int	first;
	int	second;
	int	third;

	if (!test_sort(list_a))
		return;
	tmp = *list_a;
	first = *(tmp->content);
	second = *(tmp->next->content);
	third = *(tmp->next->next->content);
	if (first > second && second < third && first < third)
		sa(list_a);
	else if (first < second && third < first)
		rra(list_a, size);
	else if (first > second && second < third)
		ra(list_a);
	else if (first > second && second > third)
		sa(list_a);
	else if (first > second && second < third)
		rra(list_a, size);
	else if (first < second && second > third && first < third)
		rra(list_a, size);
	small_sort(list_a, size);
}

void	radix(t_list **list_a, t_list **list_b, int size)
{
	(void)size;
	print_lists(*list_a, *list_b);
	//sa(list_a);
	//ra(list_a);
	//rra(list_a, size);
	//pb(list_a, list_b);
	//pa(list_a, list_b);
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
