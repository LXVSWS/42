/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:23:57 by lwyss             #+#    #+#             */
/*   Updated: 2022/05/16 00:25:37 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_symbol_size(char **line)
{
	int	size;

	if ((**line == '<' && *(*line + 1) == '<') \
	|| (**line == '>' && *(*line + 1) == '>'))
		size = 2;
	else
		size = 1;
	return (size);
}

int	check_valid_quotes(char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = line[i++];
	while (line[i] && line[i] != quote)
		i++;
	if (!line[i])
		return (0);
	return (1);
}

int	get_type(t_token *token)
{
	return (token->type);
}

int	get_word_size_with_quotes(char *line, t_list **env)
{
	int		i;
	int		size;
	char	quote;
	char	*start;

	i = 0;
	size = 0;
	quote = line[i];
	start = &line[++i];
	while (line[i] && line[i] != quote)
		i++;
	line[i] = '\0';
	size += ft_strlen(start);
	if (line[i + 1] && !ft_iswhitespace(line[i + 1]) \
	&& !check_symbol(line[i + 1]))
	{
		if (get_word_size(&line[i + 1], env) == -1)
			return (-1);
		else
			size += get_word_size(&line[i + 1], env);
	}
	line[i] = quote;
	return (size);
}

int	get_word_size(char *line, t_list **env)
{
	int	i;
	int	str_size;

	i = 0;
	str_size = 0;
	if (line[i] != '\'' && line[i] != '"')
	{
		while ((line[i] != '\0' || (line[i] != '/' \
		&& line[i + 1] != '\0')) && !ft_iswhitespace(line[i]) \
		&& !check_symbol(line[i]) && line[i] != '\'' && line[i] != '"')
			i = get_line_size(line, env, i, &str_size);
	}
	else if (line[i] == '\'' || line[i] == '"')
	{
		if (check_valid_quotes(&line[i]))
		{
			if (get_word_size_with_quotes(&line[i], env) == -1)
				return (-1);
			else
				str_size += get_word_size_with_quotes(&line[i], env);
		}
		else
			return (-1);
	}
	return (str_size);
}
