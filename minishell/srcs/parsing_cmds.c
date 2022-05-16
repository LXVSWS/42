/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:20:16 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/15 23:32:13 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	extract_word(char **line, t_token *token, t_env *env_set)
{
	int	i;
	int	len_token;

	i = 0;
	len_token = prepare_token(line, token, &env_set->envp);
	env_set->current_quote = 0;
	if (len_token == -1)
		return (0);
	while ((**line != '\0' || (**line != '/' && *(*line + 1) != '\0')) \
	&& (!ft_iswhitespace(**line) || env_set->current_quote) \
	&& (!check_symbol(**line) || env_set->current_quote))
		i = e_word_routine(line, token, env_set, i);
	(*line)++;
	token->val[i] = '\0';
	return (1);
}

int	e_word_routine(char **line, t_token *token, t_env *env_set, int i)
{
	quotes_checker(line, env_set);
	if (**line == '$' && *(*line + 1) && *(*line + 1) != '?' && \
	(*(*line + 1)) != env_set->current_quote && !ft_isdigit(*(*line + 1)))
	{
		(*line)++;
		if (ft_my_getenv(&env_set->envp, get_word(*line)) \
		&& env_set->current_quote != '\'')
		{
			i = get_env_token(line, token, &env_set->envp, i);
			if (env_set->current_quote)
				i = reset_ended_quotes(line, token, env_set, i);
		}
		else if (env_set->current_quote == '\'' && (*line)--)
			i = squote_token(line, token, env_set, i);
		else
			line_checker(line, token, env_set, i);
	}
	else if ((**line == '\'' || **line == '"') && !env_set->current_quote)
		(*line)++;
	else
		i = env_line_pos(line, token, env_set, i);
	return (i);
}

t_list	*forge(t_list *lst_tokens)
{
	t_list	*cmds;
	t_cmd	*cmd;

	cmds = NULL;
	while (lst_tokens)
	{
		cmd = get_cmd(&lst_tokens);
		if (!cmd)
			return (NULL);
		ft_lstadd_back(&cmds, ft_lstnew(cmd));
	}
	return (cmds);
}

t_cmd	*get_cmd(t_list **lst_tokens)
{
	t_params	*p;
	t_cmd		*ret_cmd;

	p = ft_calloc(1, sizeof(t_params));
	get_cmd_words(lst_tokens, p);
	*lst_tokens = p->start_lst;
	p->len = 0;
	p->i = 0;
	while (*lst_tokens && get_type((*lst_tokens)->content) != PIPE)
	{
		p->redir_type = get_type((*lst_tokens)->content);
		get_cmd_redir(p);
		*lst_tokens = (*lst_tokens)->next;
	}
	ret_cmd = get_cmd_error(lst_tokens, p);
	free(p);
	return (ret_cmd);
}

char	*get_word(char *line)
{
	int		i;
	char	*word;

	i = 0;
	while (line[i] && !ft_iswhitespace(line[i]) && line[i] != '\0' && \
	(ft_isalnum(line[i]) || line[i] == '_') && line[i] != '$' \
	&& line[i] != '\'' && line[i] != '"' && line[i] != '-')
		i++;
	word = ft_calloc(i + 1, sizeof(char));
	ft_strncpy(word, line, i);
	return (word);
}
