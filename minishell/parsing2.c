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
		else if (line[i] == '$' && getenv(&line[i + 1]))
			return (ft_strlen(getenv(&line[++i])));
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
	if (**line == '$' && getenv(*line + 1))
	{
		(*line)++;
		ft_strncpy(token->val, getenv(*line), size);
		*line += ft_strlen(*line);
	}
	else
	{
		ft_strncpy(token->val, *line, size);
		*line += size;
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

t_cmd	*get_cmd(t_list **tokens)
{
	t_token	*token;
	t_cmd	*cmd;
	void	*save;
	int		i;
	int		size;

	i = 0;
	size = 0;
	save = *tokens;
	cmd = malloc(sizeof(t_cmd));
	cmd->cmd_with_args = NULL;
	while (*tokens && get_type((*tokens)->content) != 1)
	{
		if (get_type((*tokens)->content) == 6)
			size++;
		*tokens = (*tokens)->next;
	}
	cmd->cmd_with_args = malloc(sizeof(char *) * size + 1);
	cmd->cmd_with_args[size] = 0;
	*tokens = save;
	while (*tokens && get_type((*tokens)->content) != 1)
	{
		if (get_type((*tokens)->content) == 6)
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
		if (!*tokens || get_type((*tokens)->content) == 1)
		{
			printf("syntax error : unexpected token '|'\n");
			free(cmd);
			return (NULL);
		}
	}
	return (cmd);
}

int	get_type(t_token *token)
{
	return (token->type);
}
