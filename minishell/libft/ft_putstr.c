/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:54:53 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/14 14:54:53 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		write(1, &s[i++], 1);
}

void	ft_putlst(t_list *lst)
{
	while (lst)
	{
		ft_putstr(lst->content);
		lst = lst->next;
	}
}
