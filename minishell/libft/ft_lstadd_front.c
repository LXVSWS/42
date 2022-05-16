/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:21:49 by rahmed            #+#    #+#             */
/*   Updated: 2022/02/09 19:39:55 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Add element new at the beginning of lst */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new || !lst)
		return ;
	new->next = *lst;
	*lst = new;
}

/* Delete element at the beginning of lst */
void	ft_lstdel_front(t_list **head)
{
	t_list	*tmp;

	if (!head || !*head)
		return ;
	tmp = *head;
	*head = (*head)->next;
	free(tmp);
}
