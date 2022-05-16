/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 22:03:23 by rahmed            #+#    #+#             */
/*   Updated: 2021/11/18 16:47:56 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_asciinb_fd(int n, int fd)
{
	int	u;

	u = n % 10 + '0';
	write(fd, &u, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		if (n == -2147483648)
			write(fd, "-2147483648", 11);
		else
		{
			n = n * (-1);
			write(fd, "-", 1);
		}
	}
	if ((n < 10) && (n >= 0))
		ft_asciinb_fd(n, fd);
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_asciinb_fd(n, fd);
	}
}
