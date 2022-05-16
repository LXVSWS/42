/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 23:18:01 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/14 17:10:48 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(char **arg, t_env *env, t_cmd *cmd)
{
	if (ft_strequ_hd(arg[0], "$?"))
	{
		ft_putnbr_fd(g_exit_status, 1);
		ft_putchar_fd('\n', 1);
		g_exit_status = 127;
	}
	else
		ft_print_echo(arg, env, cmd);
}

void	ft_print_echo(char **arg, t_env *env, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (ft_strequ_echo_n(arg[i + 1]))
		i++;
	if (!arg[1] || (!arg[2] && ft_is_str_blank(arg[1])))
		return (ft_putchar_fd('\n', 1));
	while (arg[++i])
	{
		if (ft_strequ_hd(arg[i], "$?"))
			ft_putnbr_fd(g_exit_status, 1);
		else
			ft_putstr_fd(arg[i], 1);
		if (env->in_redir && ft_strequ_hd(arg[i + 1], cmd->file))
			i++;
		if (arg[i + 1])
			ft_putchar_fd(' ', 1);
	}
	if (!ft_strequ_echo_n(arg[1]))
		ft_putchar_fd('\n', 1);
	g_exit_status = 0;
}

int	ft_strequ_echo_n(char const *s1)
{
	if (!s1)
		return (0);
	if (s1[0] != '-' || s1[1] != 'n')
		return (0);
	return (1);
}

void	print_error(char *msg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	ft_isbuiltin(char *args)
{
	if (ft_strequ_hd(args, "exit"))
		return (1);
	else if (ft_strequ_hd(args, "env"))
		return (1);
	else if (ft_strequ_hd(args, "$?"))
		return (1);
	else if (ft_strequ_hd(args, "unset"))
		return (1);
	else if (ft_strequ_hd(args, "export"))
		return (1);
	else if (ft_strequ_hd(args, "pwd"))
		return (1);
	else if (ft_strequ_hd(args, "cd"))
		return (1);
	else if (ft_strequ_hd(args, "echo"))
		return (1);
	return (0);
}
