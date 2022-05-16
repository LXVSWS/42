/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 00:27:30 by rahmed            #+#    #+#             */
/*   Updated: 2022/04/22 00:31:46 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		write(1, "str ", 4);
		ft_putnbr(i + 1);
		write(1, " of split\n", 10);
		ft_putstr(split[i]);
		write(1, "\n\n", 2);
		i++;
	}
}

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("tab[%d] = %s\n", i, tab[i]);
		i++;
	}
}
