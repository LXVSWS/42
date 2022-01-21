/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:24:42 by lwyss             #+#    #+#             */
/*   Updated: 2022/01/21 20:37:44 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pb(t_list **list_a, t_list **list_b)
{
	t_list	*tmp;

	tmp = *list_a;
	if (*list_a)
	{
		tmp = (*list_a)->next;
		ft_lstadd_front(list_b, *list_a);
	}
	*list_a = tmp;
	write(1, "pb\n", 3);
}

void	pa(t_list **list_a, t_list **list_b)
{
	t_list	*tmp;

	tmp = *list_b;
	if (*list_b)
	{
		tmp = (*list_b)->next;
		ft_lstadd_front(list_a, *list_b);
	}
	*list_b = tmp;
	write(1, "pa\n", 3);
}

void	sa(t_list **list_a)
{
	t_list	*tmp;
	t_list	*tmp2;

	if (*list_a && (*list_a)->next)
	{
		tmp = *list_a;
		tmp2 = (*list_a)->next->next;
		*list_a = (*list_a)->next;
		(*list_a)->next = tmp;
		(*list_a)->next->next = tmp2;
	}
	write(1, "sa\n", 3);
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

void	rra(t_list **list_a, int size)
{
	t_list	*tmp;
	t_list	*last;
	t_list	*prelast;

	tmp = *list_a;
	last = ft_lstlast(*list_a);
	prelast = *list_a;
	while (--size - 1)
		prelast = prelast->next;
	last->next = tmp;
	prelast->next = NULL;
	*list_a = last;
	write(1, "rra\n", 4);
}
