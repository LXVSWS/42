/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:03:54 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/15 23:32:25 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*env_manager(char **env, t_env *to_free, int finished)
{
	static t_env	*env_set;

	if (finished)
	{
		ft_lstclear(&(to_free->envp), free);
		ft_free_split(to_free->path);
		free(to_free);
		return (0);
	}
	if (!env_set)
	{
		env_set = ft_calloc(1, sizeof(t_env));
		if (!env_set)
			return (NULL);
		env_set->main_env = env;
		env_set->envp = ft_dpt_to_lst(env);
		if (getenv("PATH") != NULL)
			env_set->path = ft_split(getenv("PATH"), ':');
		else
			env_set->path = ft_split("/usr/bin:/bin:/usr/sbin:/sbin", ':');
		if (!(env_set->envp) || !(env_set->path))
			return (NULL);
	}
	return (env_set);
}

int	routine(t_env *env_set)
{
	int		ret;
	char	*line;

	ret = 0;
	if (env_set->no_prompt)
	{
		line = readline("");
		env_set->no_prompt = 0;
	}
	else
		line = readline(BLUE"Min"WHITE"ish"RED"ell"YELLOW"@42_Nice$> "RESET);
	env_set->stdout = dup(STDOUT_FILENO);
	env_set->stdin = dup(STDIN_FILENO);
	ft_pwd_update(&env_set->envp);
	if (handle_eof_ctrl_d(line))
		ret = -1;
	else if (!ft_is_str_blank(line) && line)
		ret = ft_minishell(env_set, line);
	close(env_set->stdout);
	close(env_set->stdin);
	free(line);
	return (ret);
}

int	ft_minishell(t_env *env_set, char *line)
{
	t_list	*cmds;
	t_list	*tokens;
	int		ret;

	ret = 0;
	add_history(line);
	tokens = tokenize(line, env_set);
	cmds = forge(tokens);
	if (cmds)
		ret = cmds_launcher(cmds, env_set);
	ft_lstclear(&tokens, free);
	ft_lstclear(&cmds, free);
	return (ret);
}

int	ft_exit_code(char **args, int print_exit)
{
	int	valid_code;

	if (print_exit)
		ft_putstr_fd("exit\n", 1);
	if (args[1] == NULL)
		return (-1);
	valid_code = ft_str_isdigit(args[1]);
	if (!valid_code)
		print_error("exit: numeric argument required");
	else if (args[2])
		print_error("exit: too many arguments");
	else if (valid_code && !args[2])
	{
		g_exit_status = ft_atoll(args[1]) % 256;
		return (-1);
	}
	return (0);
}

char	**env_maker(char **env)
{
	env = ft_calloc(5, sizeof(char *));
	if (!env)
		return (NULL);
	env[0] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin");
	env[1] = ft_strdup("PWD=/");
	env[2] = ft_strdup("SHLVL=1");
	env[3] = ft_strdup("_=/usr/bin/env");
	env[4] = NULL;
	return (env);
}
