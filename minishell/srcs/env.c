/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 13:23:34 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/14 15:40:16 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_my_getenv(t_list **env, char *key)
{
	t_list	*tmp_env;
	char	*full_key;

	full_key = ft_strjoin(key, "=");
	tmp_env = *env;
	if (ft_isdigit(key[0]) || !ft_env_alnum_underscore(key))
		return (NULL);
	while (tmp_env)
	{
		if (ft_strncmp(tmp_env->content, full_key, ft_strlen(full_key)) == 0)
			return (ft_strchr(tmp_env->content, '=') + 1);
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

char	*ft_get_env_path(char *args, t_list **env)
{
	int		i_args;
	char	*path;
	char	*tmp;

	i_args = 0;
	while (args[i_args] && args[i_args] != '/')
		i_args++;
	path = ft_calloc(i_args + 1, sizeof(char));
	ft_memcpy(path, &args[1], i_args - 1);
	tmp = ft_strjoin(ft_my_getenv(env, path), "/");
	free(path);
	path = ft_strjoin(tmp, ft_del_at_whitespace(&args[i_args + 1]));
	free(tmp);
	return (path);
}

void	ft_unset(char *args, t_list **env)
{
	int		len;
	t_list	*current;

	current = *env;
	len = get_env_name_len(args, FALSE);
	if (!len)
		return ;
	if (ft_strncmp(current->content, args, len) == 0)
	{
		ft_lstdel_front(env);
		return ;
	}
	while (current->next)
	{
		if (ft_strncmp(current->next->content, args, len) == 0)
		{
			ft_lstdel_next(current);
			return ;
		}
		current = current->next;
	}
}

void	ft_export(char *args, t_list **env)
{
	int		exist;
	t_list	*env_cpy;

	env_cpy = *env;
	exist = replace_existing_env(args, env_cpy);
	if (!exist)
		ft_lstadd_back(&env_cpy, ft_lstnew(ft_strjoin(args, "\n")));
}

void	ft_write_oldpwd(t_list **env, char *pwd)
{
	t_list	*tmp_env;

	tmp_env = *env;
	while (tmp_env)
	{
		if (ft_strncmp(tmp_env->content, "OLDPWD=", 7) == 0)
		{
			free(tmp_env->content);
			tmp_env->content = ft_strjoin("OLDPWD=", pwd);
		}
		tmp_env = tmp_env->next;
	}
}
