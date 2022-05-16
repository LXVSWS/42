/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 13:36:03 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/11 21:28:42 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_env	*env_set;

	(void)ac;
	(void)av;
	if (env[0] == NULL)
		env = env_maker(env);
	init_signal();
	env_set = env_manager(env, NULL, FALSE);
	while (1)
		if (routine(env_set) == -1)
			break ;
	env_manager(NULL, env_set, TRUE);
	termios_show_echoctl();
	return (g_exit_status);
}
