/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:20:12 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/12 19:42:18 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*tokenize(char *line, t_env *env_set)
{
	t_list	*tokens;
	t_token	*token;

	tokens = NULL;
	skip_blank(&line);
	while (*line)
	{
		token = get_token(&line, env_set);
		if (!token)
			return (NULL);
		ft_lstadd_back(&tokens, ft_lstnew((t_token *)token));
		skip_whitespace(&line);
	}
	return (tokens);
}

t_token	*get_token(char **line, t_env *env_set)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (check_symbol(**line))
	{
		if (!extract_symbol(line, token))
		{
			printf("syntax error : unexpected token\n");
			free(token);
			return (NULL);
		}
	}
	else if (!extract_word(line, token, env_set))
	{
		printf("syntax error : quotes unclosed\n");
		free(token);
		return (NULL);
	}
	return (token);
}

void	free_token(void *ptr)
{
	t_token	*tok;

	tok = ptr;
	free(tok->val);
	free(tok);
}

int	check_symbol(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	extract_symbol(char **line, t_token *token)
{
	int	size;

	size = get_symbol_size(line);
	token->val = ft_calloc(size + 1, sizeof(char));
	ft_strncpy(token->val, *line, size);
	if (**line == '|')
		token->type = PIPE;
	else if (**line == '<' && *(*line + 1) == '<')
	{
		token->type = REDIR_LL;
		if (*(*line + 2) == '<' || *(*line + 2) == '>')
			return (0);
	}
	else if (**line == '<')
		token->type = REDIR_L;
	else if (**line == '>' && *(*line + 1) == '>')
	{
		token->type = REDIR_RR;
		if (*(*line + 2) == '>' || *(*line + 2) == '<')
			return (0);
	}
	else if (**line == '>')
		token->type = REDIR_R;
	*line += size;
	return (1);
}
