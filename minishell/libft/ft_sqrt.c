/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:56:27 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/14 14:56:29 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sqrt(int nb)
{
	long	i;
	long	res;

	i = 1;
	res = 0;
	if (nb <= 0)
		return (0);
	while (res < nb)
	{
		res = i * i;
		if (res == nb)
			return (i);
		i++;
	}
	return (0);
}

/*int main ()
{


	int i = 2147483647 ;
	int r = 0;
	r = ft_sqrt(i);
	printf("%d", r);
}*/
