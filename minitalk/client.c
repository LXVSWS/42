/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:10:53 by lwyss             #+#    #+#             */
/*   Updated: 2021/12/12 17:45:57 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(int ac, char **av)
{
	int				pid;
	int				i;
	int				j;
	int				flag;
	int				c;

	if (ac == 3)
	{
		pid = atoi(av[1]);
		i = -1;
		while (av[2][++i])
		{
			j = -1;
			flag = 128;
			c = av[2][i];
			while (++j < 8)
			{
				if (c >= flag)
				{
					kill(pid, SIGUSR1);
					c -= flag;
				}
				else
					kill(pid, SIGUSR2);
				flag /= 2;
				usleep(10);
			}
		}
	}
	else
		write(1, "Error\n", 6);
}
