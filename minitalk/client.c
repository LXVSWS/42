/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:10:53 by lwyss             #+#    #+#             */
/*   Updated: 2021/12/15 17:02:17 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sendbits(char c, int pid)
{
	int	i;
	int	flag;

	i = -1;
	flag = 128;
	while (++i < 8)
	{
		if (c >= flag)
		{
			kill(pid, SIGUSR1);
			c -= flag;
		}
		else
			kill(pid, SIGUSR2);
		flag /= 2;
		usleep(100);
	}
}

int	main(int ac, char **av)
{
	int				pid;
	int				i;

	if (ac == 3)
	{
		pid = atoi(av[1]);
		i = -1;
		while (av[2][++i])
			sendbits(av[2][i], pid);
	}
	else
		write(1, "Error\n", 6);
}
