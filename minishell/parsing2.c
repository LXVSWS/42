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
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->cmd_with_args = NULL;
	return (cmd);
}
