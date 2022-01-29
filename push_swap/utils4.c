/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 19:50:51 by lwyss             #+#    #+#             */
/*   Updated: 2022/01/29 20:03:28 by lwyss            ###   ########.fr       */
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

#include <stdio.h>

void	medium_sort(t_list **list_a, t_list **list_b, int size)
{
	t_list	*tmp;
	int		*min;
	int		*sec;
	int		*max;
	int		i;
	int		**or;

	(void)list_b;
	or = stock(list_a, size);
	bubble_sort(list_a);
	tmp = *list_a;
	min = tmp->content;
	sec = tmp->next->content;
	while (tmp->next)
		tmp = tmp->next;
	max = tmp->content;
	tmp = *list_a;
	i = 0;
	while (tmp)
	{
		tmp->content = or[i++];
		tmp = tmp->next;
	}
	free(or);
	tmp = *list_a;
	while (tmp->content != min && tmp->content != sec && tmp->content != max)
	{
		ra(list_a);
		tmp = *list_a;
	}
	pb(list_a, list_b);
	tmp = *list_a;
	while (tmp->content != min && tmp->content != sec && tmp->content != max)
	{
		ra(list_a);
		tmp = *list_a;
	}
	pb(list_a, list_b);
	small_sort(list_a, 3);
	pa(list_a, list_b);
	tmp = *list_a;
	while (tmp)
	{
		printf("%i\n", *(tmp->content));
		tmp = tmp->next;
	}
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
