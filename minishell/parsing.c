#include "minishell.h"

void skip_blank(char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
}

t_list	*tokenize(char *line)
{
	t_list	*tokens;
	t_token	*token;

	tokens = NULL;
	skip_blank(&line);
	while (*line)
	{
		token = get_token(&line);
		if (!token)
			return (NULL); // need add ft_lstclear(&tokens, &free_token);
		ft_lstadd_back(&tokens, ft_lstnew(token));
		skip_blank(&line);
	}
	return (tokens);
}

t_token	*get_token(char **line)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (check_symbol(**line))
	{
		if (!extract_symbol(line, token))
		{
			printf("syntax error : unexpected token\n");
			free(token);
			return (NULL);
		}
	}
	else if (!extract_word(line, token))
	{
		printf("syntax error : quotes unclosed\n");
		free(token);
		return (NULL);
	}
	return (token);
}

int	check_symbol(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	extract_symbol(char **line, t_token *token)
{
	if (**line == '|')
		token->type = 1;
	else if (**line == '<' && *(*line + 1) == '<')
	{
		token->type = 2;
		if (*(*line + 2) == '<' || *(*line + 2) == '>')
			return (0);
	}
	else if (**line == '<')
		token->type = 3;
	else if (**line == '>' && *(*line + 1) == '>')
	{
		token->type = 4;
		if (*(*line + 2) == '>' || *(*line + 2) == '<')
			return (0);		
	}
	else if (**line == '>')
		token->type = 5;
	if ((**line == '<' && *(*line + 1) == '<') || (**line == '>' && *(*line + 1) == '>'))
		*line += 2;
	else
		(*line)++;
	token->val = NULL;
	return (1);
}
