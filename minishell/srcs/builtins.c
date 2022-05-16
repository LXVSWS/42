/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 13:21:35 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/16 17:49:29 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cmd(char **args, t_env *env, t_cmd *cmd)
{
	if (!ft_strequ_hd(*args, "$?") && (!ft_strequ_hd(*args, "echo")) \
	&& g_exit_status != -1)
		g_exit_status = 0;
	if (*args == NULL)
		return (0);
	else if (ft_strequ_hd(*args, "exit"))
		return (ft_exit_code(args, 1));
	else if (ft_strequ_hd(*args, "env"))
		ft_check_env(args, env, cmd);
	else if (ft_strequ_hd(*args, "unset"))
		ft_check_unset(args, &env->envp);
	else if (ft_strequ_hd(*args, "export"))
		ft_check_export(args, &env->envp);
	else if (ft_strequ_hd(*args, "pwd"))
		ft_pwd();
	else if (ft_strequ_hd(*args, "cd"))
		ft_cd(args, &env->envp);
	else if ((ft_strequ_hd(*args, "echo")) || (ft_strequ_hd(*args, "$?")))
		ft_echo(args, env, cmd);
	else
		return (1);
	return (0);
}

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1);
	free(pwd);
}

void	ft_cd(char **args, t_list **env)
{
	char	*oldpwd;

	if (args[1] == NULL || ft_is_str_blank(args[1]))
	{
		if (ft_my_getenv(env, "HOME") != NULL)
			my_chdir(env, ft_strdup(ft_my_getenv(env, "HOME")));
		else
			ft_putendl_fd("cd: HOME not set", 2);
	}
	else if (ft_strequ_hd(args[1], "-"))
	{
		oldpwd = ft_my_getenv(env, "OLDPWD");
		if (oldpwd)
			my_chdir(env, ft_strdup(oldpwd));
		else
			ft_putendl_fd("cd: OLDPWD not set", 2);
	}
	else
		my_chdir(env, ft_get_path(args[1], env));
	ft_pwd_update(env);
}

void	ft_pwd_update(t_list **env)
{
	char	*tmp;
	char	*cwd;
	t_list	*tmp_env;

	tmp_env = *env;
	cwd = getcwd(NULL, 0);
	tmp = ft_strjoin("PWD=", cwd);
	free(cwd);
	cwd = ft_strjoin(tmp, "\n");
	free(tmp);
	while (tmp_env)
	{
		if (ft_strncmp(tmp_env->content, "PWD=", 4) == 0)
		{
			free(tmp_env->content);
			tmp_env->content = cwd;
			return ;
		}
		tmp_env = tmp_env->next;
	}
	ft_lstadd_back(env, ft_lstnew(cwd));
}

void	ft_env(t_list **env)
{
	ft_pwd_update(env);
	ft_putlst(*env);
}
