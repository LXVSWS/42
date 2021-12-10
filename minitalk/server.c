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
		write(1, "!", 1);
}

int main(int ac, char **av)
{
	char	*pid;
    if (ac == 1)
    {
        pid = itoa(getpid());
        write(1, "PID : ", 6);
        write(1, pid, strlen(pid));
        write(1, "\n", 1);
		signal(SIGUSR1, handler);
        pause();
    }
    (void)av;
}
