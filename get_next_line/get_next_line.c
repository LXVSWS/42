/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:25:22 by lwyss             #+#    #+#             */
/*   Updated: 2021/11/04 18:34:25 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*trimline(char *line)
{
	char *res;
	int	i = 0;

	while (line && line[i] && line[i] != '\n')
		i++;
	res = malloc(sizeof(char) * (i + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (line && line[i] && line[i] != '\n')
	{
		res[i] = line[i];
		i++;
	}
	res[i] = '\n';
	res[++i] = 0;
	return (res);
}

char	*saveline(char *line)
{
	char *res;
	int	i = 0;
	int j = 0;

	while (line && line[i] && line[i] != '\n')
		i++;
	res = malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	if (!res)
		return (NULL);
	while (line && line[i])
		res[j++] = line[++i];
	res[j] = 0;
	return (res);
}

char	*get_next_line(int fd)
{
	static char *line = NULL;
	char buf[BUFFER_SIZE + 1];
	int bytes_read = BUFFER_SIZE;
	char *tmp = NULL;
	char *save = NULL;
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	while (bytes_read)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (NULL);
		buf[bytes_read] = 0;
		tmp = line;
		line = ft_strjoin(tmp, buf);
		free(tmp);
		if (ft_strchr(line, '\n'))
			break;
	}
	save = trimline(line);
	tmp = line;
	line = saveline(tmp);
	free(tmp);
	return (save);
}