/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 18:09:22 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/14 14:35:01 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_list(t_cmd *cmd, t_list *redir_lst, t_env *env)
{
	t_redir	*to_redir;
	int		ret;
	int		here_doc;

	ret = 0;
	here_doc = 0;
	while (redir_lst)
	{
		to_redir = redir_lst->content;
		if (!here_doc)
			ret = redir_manager(cmd, to_redir, env);
		if (to_redir->type == REDIR_LL)
			here_doc++;
		if (ret)
			return (ret);
		redir_lst = redir_lst->next;
	}
	return (ret);
}

int	redir_manager(t_cmd *cmd, t_redir *to_redir, t_env *env)
{
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	if (to_redir->type == REDIR_L)
		ret = redir_to_stdin(cmd->file, env);
	else if (to_redir->type == REDIR_LL)
		ret = redir_heredoc(cmd->file, env);
	else if (to_redir->type == REDIR_RR)
		ret = redir_to_stdout(cmd->file, O_APPEND, env);
	else if (to_redir->type == REDIR_R)
		ret = redir_to_stdout(cmd->file, O_TRUNC, env);
	return (ret);
}

char	*ft_myreadline(char *prompt)
{
	char	*line;
	int		i;

	i = 0;
	if (g_exit_status != -2)
		ft_putstr_fd(prompt, STDIN_FILENO);
	line = ft_get_next_line_exit(STDIN_FILENO);
	if (!(ft_isin(line, '\n')) && g_exit_status != 130 && g_exit_status != 1)
		g_exit_status = -2;
	else if (g_exit_status != 130 && g_exit_status != 1)
		g_exit_status = -1;
	if (handle_eof_ctrl_d(line))
		return (NULL);
	while (line[i] && g_exit_status != 130 && g_exit_status != 1)
	{
		if (line[i] == '\n')
			line[i] = '\0';
		i++;
	}
	if (g_exit_status == 130 || g_exit_status == 1)
		return (NULL);
	return (line);
}
