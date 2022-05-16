/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 00:20:13 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/16 00:24:02 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_closed_quotes(char *line)
{
	int	i;
	int	nb_dquote;
	int	nb_squote;

	i = 0;
	nb_dquote = 0;
	nb_squote = 0;
	while (line[i])
	{
		if (line[i] == DQUOTE)
			nb_dquote++;
		else if (line[i] == SQUOTE)
			nb_squote++;
		i++;
	}
	if (nb_dquote % 2 == 0 && nb_squote % 2 == 0)
		return (1);
	return (0);
}
