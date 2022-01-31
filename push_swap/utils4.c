/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 19:50:51 by lwyss             #+#    #+#             */
/*   Updated: 2022/01/31 15:08:05 by lwyss            ###   ########.fr       */
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
	int		first;
	int		second;
	int		third;

	if (!test_sort(list_a))
		return ;
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

void	bubble_sort(t_list **list)
{
	t_list	*tmp;
	int		*val;

	tmp = *list;
	while (test_sort(list))
	{
		tmp = *list;
		while (tmp->next)
		{
			if (*(tmp->content) > *(tmp->next->content))
			{
				val = tmp->next->content;
				tmp->next->content = tmp->content;
				tmp->content = val;
			}
			tmp = tmp->next;
		}
	}
}

void	medium_sort(t_list **list_a, t_list **list_b, int size)
{
	t_list	*tmp;
	int		**val;
	int		**or;

	or = stock(list_a, size);
	bubble_sort(list_a);
	val = malloc(sizeof(int *) * 3);
	tmp = *list_a;
	val[0] = tmp->content;
	val[1] = tmp->next->content;
	while (tmp->next)
		tmp = tmp->next;
	val[2] = tmp->content;
	replace_list(list_a, or);
	free(or);
	final_sort(list_a, list_b, val);
}

void	radix_sort(t_list **list_a, t_list **list_b, int size)
{
	t_list	*tmp;
	int		i;
	int		j;

	tmp = *list_a;
	i = -1;
	j = 0;
	while (test_sort(list_a))
	{
		while (++i < size)
		{
			if (((*(tmp->content) >> j & 1) == 1))
				ra(list_a);
			else
				pb(list_a, list_b);
			tmp = *list_a;
		}
		while ((*list_b))
			pa(list_a, list_b);
		tmp = *list_a;
		i = -1;
		j++;
	}
}
