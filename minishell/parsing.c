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

int	check_symbol(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
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

int	extract_symbol(char **line, t_token *token)
{
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
	if ((**line == '<' && *(*line + 1) == '<')\
	 || (**line == '>' && *(*line + 1) == '>'))
		*line += 2;
	else
		(*line)++;
	token->val = NULL;
	return (1);
}

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

char	*get_word(char *line)
{
	int		i;
	char	*word;

	i = 0;
	while ((line[i] && !is_whitespace(line[i]) \
	&& (line[i] >= 65 && line[i] <= 90)) || \
	(line[i] >= 97 && line[i] <= 122) || line[i] == 95)
		i++;
	word = malloc(sizeof(char) * i);
	ft_strncpy(word, line, i);
	return (word);
}

int	get_word_size(char *line)
{
	int		i;

	i = 0;
	while (line[i] && (line[i] != ' ' && line[i] != '\t') && !check_symbol(line[i]))
	{
		if (line[i] == '$' && getenv(get_word(&line[i + 1])))
			return (i + ft_strlen(getenv(get_word(&line[i + 1]))));
		i++;
	}
	return (i);
}

int	extract_word(char **line, t_token *token)
{
	int	size;
	int i;
	int j;
	char *varenv;

	i = 0;
	j = 0;
	size = get_word_size(*line);
	token->type = WORD;
	token->val = malloc(sizeof(char) * size + 1);
	token->val[size] = 0;
	while (i < size)
	{
		if (**line == '$' && getenv(get_word(*line + 1)))
		{
			(*line)++;
			varenv = getenv(get_word(*line));
			while (varenv[j])
			{
				token->val[i] = varenv[j];
				i++;
				j++;
			}
			*line += ft_strlen(get_word(*line));
		}
		else
		{
			token->val[i] = **line;
			(*line)++;
		}
		i++;
	}
	return (1);
}

t_list	*forge(t_list *tokens)
{
	t_list	*cmds;
	t_cmd	*cmd;

	cmds = NULL;
	while (tokens)
	{
		cmd = get_cmd(&tokens);
		if (!cmd)
			return (NULL); // need add ft_lstclear(&cmds, &free_cmd);
		ft_lstadd_back(&cmds, ft_lstnew(cmd));
	}
	return (cmds);
}

int	get_type(t_token *token)
{
	return (token->type);
}

t_cmd	*allocate_cmd_size(t_list *tokens)
{
	t_cmd	*cmd;
	int		size;

	size = 0;
	cmd = malloc(sizeof(t_cmd));
	cmd->cmd_with_args = NULL;
	while (tokens && get_type(tokens->content) != PIPE)
	{
		if (get_type(tokens->content) == WORD)
			size++;
		tokens = tokens->next;
	}
	cmd->cmd_with_args = malloc(sizeof(char *) * size + 1);
	cmd->cmd_with_args[size] = NULL;
	return (cmd);
}

t_cmd	*get_cmd(t_list **tokens)
{
	t_token	*token;
	t_cmd	*cmd;
	int		i;
	int		size;

	i = 0;
	size = 0;
	cmd = allocate_cmd_size(*tokens);
	while (*tokens && get_type((*tokens)->content) != PIPE)
	{
		if (get_type((*tokens)->content) == WORD)
		{
			token = (*tokens)->content;
			size = ft_strlen(token->val);
			cmd->cmd_with_args[i] = malloc(sizeof(char) * size + 1);
			ft_strncpy(cmd->cmd_with_args[i++], token->val, size);
		}
		*tokens = (*tokens)->next;
	}
	if (*tokens)
	{
		*tokens = (*tokens)->next;
		if (!*tokens || get_type((*tokens)->content) == PIPE \
		|| get_type((*tokens)->content) == REDIR_L \
		|| get_type((*tokens)->content) == REDIR_LL \
		|| get_type((*tokens)->content) == REDIR_R \
		|| get_type((*tokens)->content) == REDIR_RR)
		{
			printf("syntax error near unexpected token '|'\n");
			free(cmd);
			return (NULL);
		}
	}
	return (cmd);
}
