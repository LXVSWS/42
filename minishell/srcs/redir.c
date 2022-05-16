/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:19:17 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/14 14:45:09 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_heredoc(char *stop, t_env *env)
{
	char	**hd;
	int		fd_heredoc;
	int		i;

	i = -1;
	fd_heredoc = open(".heredoc_tmp", O_CREAT | O_RDWR | \
	O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd_heredoc == -1)
		return (OP_ERROR);
	hd = here_doc(stop, env);
	while (hd[++i] && g_exit_status != 130 && g_exit_status != 1)
		ft_putendl_fd(hd[i], fd_heredoc);
	close(fd_heredoc);
	usleep(2000);
	env->file_fd_in = open(".heredoc_tmp", O_RDONLY);
	ft_free_split(hd);
	return (SUCCESS);
}

char	**here_doc(char *stop, t_env *env)
{
	char	**tab;
	t_list	*lst;

	env->no_exit = 1;
	lst = heredoc_list_line(stop, env);
	if (g_exit_status == 130 || g_exit_status == 1)
	{
		ft_lstclear(&lst, &ft_lstdel_content);
		if (env->file_fd_in)
			env->file_fd_in = close(env->file_fd_in);
		dup2(env->stdin, STDIN_FILENO);
	}
	tab = ft_lst_to_dpt(lst);
	ft_lstclear(&lst, free);
	return (tab);
}

t_list	*heredoc_list_line(char *stop, t_env *env)
{
	char	*rd_ret;
	t_list	*lst;

	rd_ret = NULL;
	lst = NULL;
	while (env->no_exit && g_exit_status != 130 && g_exit_status != 1)
	{
		rd_ret = ft_myreadline("> ");
		if (rd_ret == NULL)
			break ;
		else if (!ft_strequ_hd(rd_ret, stop) && g_exit_status != 130 \
		&& g_exit_status != 1)
		{
			if (!ft_strequ_hd(rd_ret, "\0"))
				ft_lstadd_back(&lst, ft_lstnew(ft_strdup(rd_ret)));
		}
		else
			env->no_exit = 0;
		if (rd_ret != NULL)
			free(rd_ret);
	}
	return (lst);
}

int	redir_to_stdout(void *file, int mod, t_env *env)
{
	if (file == NULL || ft_strequ_hd(file, "|"))
		return (OUT_ERROR);
	if (mod == O_TRUNC)
	{
		env->file_fd_out = open(file, O_CREAT | O_RDWR | \
		O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
	}
	else if (mod == O_APPEND)
	{
		env->file_fd_out = open(file, O_CREAT | O_RDWR | \
		O_APPEND, S_IRWXU | S_IRWXG | S_IRWXO);
	}
	if (env->file_fd_out == -1)
		return (OP_ERROR);
	return (0);
}

int	redir_to_stdin(void *file, t_env *env)
{
	if (access(file, F_OK) == -1)
		return (BF_ERROR);
	env->file_fd_in = open(file, O_RDONLY);
	if (env->file_fd_in == -1)
		return (OP_ERROR);
	return (0);
}
