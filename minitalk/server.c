/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:11:03 by lwyss             #+#    #+#             */
/*   Updated: 2021/12/10 16:47:01 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int signum)
{
	if (signum == SIGUSR1)
		write(1, "0", 1);
    else if (signum == SIGUSR2)
		write(1, "1", 1);
    write(1, "\n", 1);
}

int main()
{
	char	*pid;
    pid = itoa(getpid());
    write(1, "PID : ", 6);
    write(1, pid, strlen(pid));
    write(1, "\nWaiting client...\n", 19);
    if (signal(SIGUSR1, handler) == SIG_ERR)
    {
        return (write(1, "Error\n", 6));
        exit(-1);
    }
    if (signal(SIGUSR2, handler) == SIG_ERR)
    {
        return (write(1, "Error\n", 6));
        exit(-1);
    }
    while (1);
}
