/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:11:03 by lwyss             #+#    #+#             */
/*   Updated: 2021/12/15 17:03:10 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile unsigned char	g_count = 0;

void	handler(int signum)
{
	static unsigned char	byte = 0;

	if (signum == SIGUSR1)
	{
		byte <<= 1;
		byte++;
		g_count++;
	}
	if (signum == SIGUSR2)
	{
		byte <<= 1;
		g_count++;
	}
	if (g_count >= 8)
	{
		write(1, &byte, 1);
		g_count = 0;
		byte = 0;
	}
}

int	main(void)
{
	char				*pid;
	struct sigaction	sigact;

	pid = itoa(getpid());
	write(1, "PID : ", 6);
	write(1, pid, strlen(pid));
	write(1, "\nWaiting client...\n", 19);
	sigact.sa_handler = handler;
	if (sigaction(SIGUSR1, &sigact, NULL) == -1)
	{
		return (write(1, "Error\n", 6));
		exit(-1);
	}
	if (sigaction(SIGUSR2, &sigact, NULL) == -1)
	{
		return (write(1, "Error\n", 6));
		exit(-1);
	}
	while (1)
		;
	return (0);
}
