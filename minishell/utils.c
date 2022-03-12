#include "minishell.h"

void	skip_blank(char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
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
		if (*(*line + 2) == '<')
			return (0);
	}
	else if (**line == '<')
		token->type = 3;
	else if (**line == '>' && *(*line + 1) == '>')
	{
		token->type = 4;
		if (*(*line + 2) == '>')
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

void	ft_strncpy(char *dst, const char *src, int n)
{
	int	i;

	if (!dst || !src || n < 0)
		return ;
	i = 0;
	while (src[i] && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
}
