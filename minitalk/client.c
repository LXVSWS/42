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

char	*atob(char *s)
{
	char	*b;
	int		i;
	int		len;

	len = strlen(s) * 8;
	b = malloc(sizeof(char) * len + 1);
	if (!b)
		return (NULL);
	i = -1;
	while (s[++i])
		atob_calc(b, s[i], i);
	b[len] = 0;
	return (b);
}

int	main(int ac, char **av)
{
	char	*b;
	int		i;

	if (ac == 3)
	{
		b = atob(av[2]);
		i = 0;
		while (b[i])
		{
			if (b[i] == '0')
				kill(atoi(av[1]), SIGUSR1);
			else if (b[i] == '1')
				kill(atoi(av[1]), SIGUSR2);
			i++;
			usleep(10);
		}
		free(b);
	}
	else
		write(1, "Error\n", 6);
}
