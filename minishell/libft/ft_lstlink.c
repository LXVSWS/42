/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlink.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:52:40 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/14 14:52:43 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstlink_rm(t_list **start, void *data_ref)
{
	t_list	*tmp;
	t_list	*to_free;

	if (!data_ref)
		return ;
	to_free = ft_lst_find(*start, data_ref);
	if (!ft_strequ_hd(data_ref, (*start)->content))
	{
		tmp = ft_lst_find_before(*start, data_ref);
		tmp->next = tmp->next->next;
	}
	else
		*start = (*start)->next;
	if (to_free->content)
		free(to_free->content);
	free(to_free);
	to_free = NULL;
}

void	ft_lstlink_new(t_list **start, void *to_del, void *new)
{
	t_list	*left_link;
	t_list	*right_link;

	if (!to_del || !new)
		return ;
	left_link = ft_lst_find_before(*start, to_del);
	right_link = left_link->next->next;
	ft_lstlink_rm(start, to_del);
	left_link->next = ft_lstnew(ft_strdup(new));
	left_link->next->next = right_link;
}
