#include "minishell.h"

int	get_word_size(char *line)
{
	int		i;
	char	quote;
	
	i = 0;
	while (line[i] && (line[i] != ' ' && line[i] != '\t') && !check_symbol(line[i]))
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
			if (!line[i])
				return (-1);
		}
		i++;
	}
	return (i);
}

int	extract_word(char **line, t_token *token)
{
	int	size;

	size = get_word_size(*line);
	if (size == -1)
		return (0);
	token->type = 6;
	token->val = malloc(sizeof(char) * size + 1);
	ft_strncpy(token->val, *line, size);
	*line += size;
	return (1);
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
