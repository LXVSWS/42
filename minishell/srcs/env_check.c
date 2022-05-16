/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 23:34:00 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/14 16:50:18 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_check_unset(char **args, t_list **env)
{
	int	unset_key;

	unset_key = 1;
	while (args[unset_key] != NULL)
	{
		ft_unset(args[unset_key], env);
		unset_key++;
	}
}

void	ft_check_export(char **args, t_list **env)
{
	int	export_key;

	if (args[1] == NULL)
		ft_print_export(env);
	else
	{
		export_key = 1;
		while (args[export_key] != NULL)
		{
			if (!ft_isdigit(args[export_key][0]) &&
			ft_env_alnum_underscore(args[export_key]))
				ft_export(args[export_key], env);
			else
				print_error("export: not a valid identifier");
			export_key++;
		}
	}
}

void	ft_print_export(t_list **env)
{
	char	**lines;
	t_list	*tmp_env;

	tmp_env = *env;
	while (tmp_env)
	{
		lines = ft_split(tmp_env->content, '=');
		ft_printf("declare -x %s=\"%s\"\n", lines[0], ft_del_nl(lines[1]));
		ft_free_tab(lines);
		tmp_env = tmp_env->next;
	}
}

int	ft_env_alnum_underscore(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && (str[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}

void	ft_check_env(char **args, t_env *env, t_cmd *cmd)
{
	if ((args[1] == NULL) || env->in_redir)
		ft_env(&env->envp);
	else if (!ft_strequ_hd(args[1], "cd"))
	{
		if ((args[2] == NULL) && \
		((access(parse_cmd(env->path, args + 1), F_OK)) == 0))
		{
			if (ft_cmd(args + 1, env, cmd) > 0)
				ft_check_exec_child_cmd((args + 1), env);
		}
		else
		{
			ft_putendl_fd("No such file or directory", 2);
			g_exit_status = 1;
		}
	}
}
