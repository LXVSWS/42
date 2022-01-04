/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:11:03 by lwyss             #+#    #+#             */
/*   Updated: 2022/01/04 16:43:33 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int signum)
{
	static char	byte = 0;
	static char	count = 0;

	if (signum == SIGUSR1)
	{
		byte <<= 1;
		byte++;
		count++;
	}
	if (signum == SIGUSR2)
	{
		byte <<= 1;
		count++;
	}
	if (count >= 8)
	{
		write(1, &byte, 1);
		count = 0;
		byte = 0;
	}
}

int	main(void)
{
	char				*pid;

	pid = itoa(getpid());
	write(1, "PID : ", 6);
	write(1, pid, strlen(pid));
	write(1, "\nWaiting client...\n", 19);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
		pause();
	return (0);
}
