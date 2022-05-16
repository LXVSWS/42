/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_nbchr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:57:37 by rahmed            #+#    #+#             */
/*   Updated: 2021/11/14 16:58:17 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_nbchr(char *s, int *nbchr)
{
	if (!s)
		return (ft_putstr_nbchr("(null)", nbchr));
	while (*s)
		ft_putchar_nbchr(*s++, nbchr);
}
