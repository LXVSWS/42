/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:23:57 by lwyss             #+#    #+#             */
/*   Updated: 2022/05/15 23:32:51 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_fake_env_line_size(char *line, int i)
{
	while (line[i] != '\0' && !ft_iswhitespace(line[i]) \
	&& !check_symbol(line[i]) && line[i] != '$' && \
	ft_isalnum(line[i]))
		i++;
	return (i);
}

int	get_line_size(char *line, t_list **env, int i, int *str)
{
	if (line[i] == '$' && line[i + 1] && line[i + 1] != '?')
	{
		i++;
		if (ft_my_getenv(env, get_word(&line[i])))
		{
			*str += ft_strlen(ft_del_nl \
			(ft_my_getenv(env, (get_word(&line[i])))));
			i += ft_strlen(get_word(&line[i]));
		}
		else
			i = get_fake_env_line_size(line, i);
	}
	else
	{
		i++;
		(*str)++;
	}
	return (i);
}

int	get_env_token(char **line, t_token *token, t_list **env, int i)
{
	size_t	j;
	char	*varenv;

	j = 0;
	varenv = ft_del_nl(ft_my_getenv(env, get_word(*line)));
	while (varenv[j])
		token->val[i++] = varenv[j++];
	(*line) += ft_strlen(get_word(*line));
	return (i);
}

void	line_checker(char **line, t_token *token, t_env *env_set, int i)
{
	while (**line != ' ' && ft_isalnum(**line) \
	&& !check_symbol(**line) && (**line != '$') && \
	(**line != '\0') && **line != '\'' && **line != '"')
		(*line)++;
	i = reset_ended_quotes(line, token, env_set, i);
	while (ft_iswhitespace(**line) && !i)
		(*line)++;
}

int	squote_token(char **line, t_token *token, t_env *env_set, int i)
{
	while (**line != '\0' && **line != '\'')
		token->val[i++] = *(*line)++;
	if (*(*line)++ == '\'')
		env_set->current_quote = 0;
	return (i);
}
