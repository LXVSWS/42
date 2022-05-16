/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 23:43:19 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/16 00:19:21 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmds_init(t_list *lstcmd, t_env *env_set)
{
	env_set->oldstdin = 0;
	env_set->file_fd_in = 0;
	env_set->file_fd_out = 0;
	if (((t_cmd *)lstcmd->content)->redir_in \
	|| ((t_cmd *)lstcmd->content)->redir_out)
		env_set->in_redir = 1;
	else
		env_set->in_redir = 0;
}

int	cmds_launcher(t_list *lstcmd, t_env *env_set)
{
	int	ret;
	int	listsize;

	cmds_init(lstcmd, env_set);
	listsize = ft_lstsize(lstcmd);
	while (lstcmd)
	{
		ret = cmds_exec(lstcmd, env_set);
		if ((error_printer(ret) != SUCCESS) || (lstcmd->next == NULL))
			break ;
		lstcmd = lstcmd->next;
	}
	while (listsize--)
	{
		waitpid(-1, NULL, 0);
		if (WIFEXITED(env_set->pid))
			g_exit_status |= WEXITSTATUS(env_set->pid);
	}
	if (!access(".heredoc_tmp", F_OK))
		unlink(".heredoc_tmp");
	if (ret == -1)
		return (-1);
	return (SUCCESS);
}

int	cmds_exec(t_list *lstcmd, t_env *env)
{
	int		ret;
	int		exec;
	t_cmd	*cmd;

	ret = 0;
	cmd = lstcmd->content;
	exec = EXEC_CHILD;
	ret = redir_list(cmd, cmd->redir_in, env);
	if (ret)
		return (ret);
	if (lstcmd->next)
		exec = EXEC_PIPE;
	if (!lstcmd->next)
	{
		ret = redir_list(cmd, cmd->redir_out, env);
		if (ret)
			return (ret);
		exec = EXEC_MAIN;
	}
	ret = launch_exec(env, cmd, exec);
	return (ret);
}

int	launch_exec(t_env *env, t_cmd *cmd, int exec)
{
	int	ret;

	ret = 0;
	if (exec == EXEC_PIPE)
	{
		if (ft_strchr(cmd->cmd_with_args[0], '/'))
			env->cmd_path = ft_strdup(cmd->cmd_with_args[0]);
		else
			env->cmd_path = parse_cmd(env->path, cmd->cmd_with_args);
		ft_pipe(cmd, env);
		if (env->cmd_path)
			free(env->cmd_path);
	}
	else if (exec == EXEC_CHILD)
	{
		ret = redir_list(cmd, cmd->redir_out, env);
		if (ret)
			return (ret);
		ret = exec_in_child(cmd, env);
	}
	else if (exec == EXEC_MAIN)
		ret = exec_in_main(cmd, env);
	env->cmd_path = NULL;
	return (ret);
}
