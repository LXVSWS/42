/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:55:54 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/10 20:30:20 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_signal(void)
{
	struct sigaction	action;
	sigset_t			set;

	termios_hide_echoctl();
	signal(SIGQUIT, SIG_IGN);
	sigemptyset(&set);
	sigaddset(&set, SIGINT | SIGQUIT);
	action.sa_handler = signal_handler;
	action.sa_mask = set;
	action.sa_flags = SA_NODEFER;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

void	signal_handler(int signo)
{
	g_exit_status = 128 + signo;
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		g_exit_status = 1;
	}
	if (g_exit_status >= 0)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

int	handle_eof_ctrl_d(char *str)
{
	if (str == NULL)
	{
		if (g_exit_status >= 0)
			ft_putstr_fd("exit\n", 1);
		g_exit_status = 0;
		return (1);
	}
	return (0);
}

void	termios_hide_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	term.c_lflag |= (ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	termios_show_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= (ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
