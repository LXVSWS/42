/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_launcher_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:20:29 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/14 14:44:34 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_non_builtin_parent(t_env *env)
{
	wait(&env->pid);
	if (env->oldstdin)
		env->oldstdin = close(env->oldstdin);
	if (env->file_fd_in)
		env->file_fd_in = close(env->file_fd_in);
	dup2(env->stdin, STDIN_FILENO);
	if (env->oldstdout)
		env->oldstdout = close(env->oldstdout);
	if (env->file_fd_out)
		env->file_fd_out = close(env->file_fd_out);
	dup2(env->stdout, STDOUT_FILENO);
}

char	**ft_set_cmdtoexec(t_cmd *cmd)
{
	char	**cmd_to_exec;
	int		i;

	i = 0;
	if (!cmd->redir_in && !cmd->redir_out)
	{
		while (cmd->cmd_with_args[i])
			i++;
		cmd_to_exec = (char **)ft_calloc(i + 1, sizeof(char *));
		i = 0;
		while (cmd->cmd_with_args[i])
		{
			cmd_to_exec[i] = ft_strdup(cmd->cmd_with_args[i]);
			i++;
		}
		cmd_to_exec[i] = (char *)0;
	}
	else
		cmd_to_exec = ft_set_cmdtoexec_redir(cmd);
	return (cmd_to_exec);
}

char	**ft_set_cmdtoexec_redir(t_cmd *cmd)
{
	if (cmd->redir_out)
		return (ft_set_cmdtoexec_redir_out(cmd));
	else
		return (ft_set_cmdtoexec_redir_in(cmd));
}

char	**ft_set_cmdtoexec_redir_out(t_cmd *cmd)
{
	t_redir	*redir_out;
	char	**cmd_to_exec;
	int		i;
	int		len;

	i = 0;
	len = ft_lstsize(cmd->redir_out);
	cmd_to_exec = (char **)ft_calloc(len + 1, sizeof(char *));
	while (cmd->redir_out)
	{
		redir_out = (t_redir *)cmd->redir_out->content;
		cmd_to_exec[i] = ft_strdup(redir_out->word);
		cmd->redir_out = cmd->redir_out->next;
		i++;
	}
	cmd_to_exec[i] = (char *)0;
	return (cmd_to_exec);
}

char	**ft_set_cmdtoexec_redir_in(t_cmd *cmd)
{
	t_redir	*redir_in;
	char	**cmd_to_exec;
	int		i;
	int		len;

	i = 0;
	len = ft_lstsize(cmd->redir_in);
	cmd_to_exec = (char **)ft_calloc(len + 1, sizeof(char *));
	while (cmd->redir_in)
	{
		redir_in = (t_redir *)cmd->redir_in->content;
		cmd_to_exec[i] = ft_strdup(redir_in->word);
		cmd->redir_in = cmd->redir_in->next;
		i++;
	}
	cmd_to_exec[i] = (char *)0;
	return (cmd_to_exec);
}
