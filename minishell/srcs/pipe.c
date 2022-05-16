/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 23:18:45 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/14 16:50:49 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pipe(t_cmd *cmd, t_env *env)
{
	if (pipe(env->pipe_fd) == -1)
		return ;
	env->pid = fork();
	if (env->pid == EXEC_CHILD)
	{
		close(env->pipe_fd[0]);
		dup2(env->pipe_fd[1], STDOUT_FILENO);
		close(env->pipe_fd[1]);
		dup2(env->oldstdin, STDIN_FILENO);
		exec_in_pipe(cmd, env);
		exit (0);
	}
	else
	{
		close(env->pipe_fd[1]);
		if (env->oldstdin)
			close(env->oldstdin);
		env->oldstdin = env->pipe_fd[0];
	}
}

void	exec_in_pipe(t_cmd *cmd, t_env *env)
{
	int	ret;

	ret = redir_list(cmd, cmd->redir_out, env);
	if (ret)
		exit(1);
	if (ft_cmd(cmd->cmd_with_args, env, cmd) > 0)
		ft_check_exec_pipe(cmd, env);
}

void	ft_check_exec_pipe(t_cmd *cmd, t_env *env)
{
	char	**args;

	args = ft_set_cmdtoexec(cmd);
	if (ft_strchr(*args, '/'))
		env->cmd_path = ft_strdup(*args);
	else
		env->cmd_path = parse_cmd(env->path, args);
	if (access(env->cmd_path, F_OK | X_OK) == SUCCESS)
		g_exit_status = 0;
	else
		g_exit_status = 127;
	if (ft_cmd(args, env, cmd) > 0)
	{
		dup2(env->oldstdin, STDIN_FILENO);
		execve(env->cmd_path, args, env->main_env);
	}
	exit(0);
}

char	*parse_cmd(char **path, char **cmd)
{
	char	*cmd_path;
	char	*tmp;
	size_t	i;

	tmp = ft_strjoin("/", cmd[0]);
	i = -1;
	while (path[++i])
	{
		cmd_path = ft_strjoin(path[i], tmp);
		if (access(cmd_path, F_OK | X_OK) == SUCCESS)
		{
			free(tmp);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free(tmp);
	return (NULL);
}
