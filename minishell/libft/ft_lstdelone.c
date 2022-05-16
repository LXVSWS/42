/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 19:07:30 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/07 23:42:50 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	if (del != NULL && lst->content != NULL)
		(*del)(lst->content);
	free(lst);
	lst = NULL;
}

void	ft_lstdel_next(t_list *current)
{
	t_list	*tmp;

	if (current == NULL || current->next == NULL)
		return ;
	tmp = current->next;
	current->next = tmp->next;
	free(tmp);
}
