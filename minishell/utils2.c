#include "minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*l;

	l = malloc(sizeof(t_list));
	if (!l)
		return (NULL);
	l->content = content;
	l->next = NULL;
	return (l);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*tmp;

	tmp = *alst;
	if (*alst)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*alst = new;
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
			return (NULL); // need add lstclear tokens
		ft_lstadd_back(&tokens, ft_lstnew(token));
		skip_blank(&line);
	}
	return (tokens);
}
