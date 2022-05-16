/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:23:57 by lwyss             #+#    #+#             */
/*   Updated: 2022/05/16 00:13:49 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_line_pos(char **line, t_token *token, t_env *env_set, int i)
{
	if (**line == '$' && ft_isdigit(*(*line + 1)))
		(*line) += 2;
	if (**line == '$' && *(*line + 1) && *(*line + 1) != '?' && \
	*(*line + 1) != env_set->current_quote && !ft_isdigit(*(*line + 1)))
		(*line)++;
	token->val[i] = **line;
	i++;
	(*line)++;
	return (i);
}

void	quotes_checker(char **line, t_env *env_set)
{
	if (**line == '\'' || **line == '"')
	{
		if (!(env_set->current_quote))
			env_set->current_quote = *(*line)++;
		else if (**line == env_set->current_quote)
			env_set->current_quote = 0;
	}
}

int	reset_ended_quotes(char **line, t_token *token, t_env *env_set, int i)
{
	if (**line == '\'' || **line == '"')
	{
		if (**line == '\'')
		{
			token->val[i] = '\'';
			i++;
		}
		(*line)++;
		env_set->current_quote = 0;
	}
	return (i);
}

int	prepare_token(char **line, t_token *token, t_list **env)
{
	int		size;

	if (!check_closed_quotes(*line))
		return (-1);
	size = get_word_size(*line, env);
	if (size == -1)
		return (-1);
	token->type = WORD;
	token->val = ft_calloc(size + 2, sizeof(char));
	return (size);
}

t_cmd	*allocate_cmd_size(t_list *lst_tokens)
{
	t_cmd	*cmd;
	int		size;

	size = 0;
	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->cmd_with_args = NULL;
	while (lst_tokens && get_type(lst_tokens->content) != PIPE)
	{
		if (get_type(lst_tokens->content) == WORD)
			size++;
		lst_tokens = lst_tokens->next;
	}
	cmd->cmd_with_args = ft_calloc(size + 1, sizeof(char *));
	cmd->cmd_with_args[size] = 0;
	cmd->cmd_redir = ft_calloc(1, sizeof(t_redir));
	return (cmd);
}
