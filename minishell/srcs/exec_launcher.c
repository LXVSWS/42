/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_launcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:20:29 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/14 16:43:41 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_in_main(t_cmd *cmd, t_env *env)
{
	int	ret;

	ret = 0;
	env->no_exec = 0;
	if ((g_exit_status == 130 || g_exit_status == 1) && env->file_fd_in)
		env->no_exec = 1;
	if (ft_isbuiltin(cmd->cmd_with_args[0]))
		ret = exec_builtin(cmd, env);
	else
		ret = exec_in_child(cmd, env);
	return (ret);
}

int	exec_builtin(t_cmd *cmd, t_env *env)
{
	int	ret;

	ret = 0;
	if (env->oldstdin)
		dup2(env->oldstdin, STDIN_FILENO);
	if (env->oldstdout)
		dup2(env->oldstdout, STDOUT_FILENO);
	if (env->file_fd_out)
		dup2(env->file_fd_out, STDOUT_FILENO);
	if (env->file_fd_in)
		dup2(env->file_fd_in, STDIN_FILENO);
	if (!env->no_exec)
		ret = ft_cmd(cmd->cmd_with_args, env, cmd);
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
	return (ret);
}

int	exec_in_child(t_cmd *cmd, t_env *env)
{
	int	ret;
	int	i;

	i = 0;
	env->cmd_path = ft_check_exec_child_cmd(ft_set_cmdtoexec(cmd), env);
	ret = ft_isbuiltin(cmd->cmd_with_args[0]);
	if (!ret && !env->cmd_path)
		return (CMD_ERROR);
	return (0);
}

char	*ft_check_exec_child_cmd(char **cmd, t_env *env)
{
	if (ft_strchr(*cmd, '/'))
		env->cmd_path = ft_strdup(*cmd);
	else
		env->cmd_path = parse_cmd(env->path, cmd);
	if ((g_exit_status == 130 || g_exit_status == 1) && env->file_fd_in)
		env->no_exec = 1;
	else
		env->no_exec = 0;
	if (access(env->cmd_path, F_OK | X_OK) == SUCCESS)
		g_exit_status = 0;
	else
		g_exit_status = 127;
	if (ft_strequ_hd(cmd[0], "cat") && cmd[1] == NULL && !env->file_fd_in)
		env->no_prompt = 1;
	env->pid = fork();
	if (env->pid == EXEC_CHILD)
		exec_non_builtin_child(cmd, env);
	else
		exec_non_builtin_parent(env);
	return (env->cmd_path);
}

void	exec_non_builtin_child(char **cmd, t_env *env)
{
	if (env->oldstdin)
		dup2(env->oldstdin, STDIN_FILENO);
	if (env->file_fd_in)
		dup2(env->file_fd_in, STDIN_FILENO);
	if (env->oldstdout)
		dup2(env->oldstdout, STDOUT_FILENO);
	if (env->file_fd_out)
		dup2(env->file_fd_out, STDOUT_FILENO);
	if (!env->no_exec)
		execve(env->cmd_path, cmd, env->main_env);
	exit(0);
}
