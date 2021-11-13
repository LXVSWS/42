/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:15:15 by lwyss             #+#    #+#             */
/*   Updated: 2021/11/13 19:11:44 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*trimline(char *save)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		line = malloc(sizeof(char) * (i + 2));
	else
		line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = -1;
	while (save[++i] && save[i] != '\n')
		line[i] = save[i];
	if (save[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = 0;
	return (line);
}

char	*restline(char *save)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i])
	{
		line = malloc(sizeof(char) * (ft_strlen(save) - i + 1));
		if (!line)
			return (NULL);
		while (save[i])
			line[j++] = save[++i];
		line[j] = 0;
		free(save);
		return (line);
	}
	else
	{
		free(save);
		return (NULL);
	}
}

char	*get_next_line(int fd)
{
	static char	*save[FD_MAX];
	char		*line;
	char		buf[BUFFER_SIZE + 1];
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FD_MAX)
		return (NULL);
	bytes_read = 1;
	while (bytes_read && !ft_strchr(save[fd], '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		buf[bytes_read] = 0;
		save[fd] = ft_strjoin(save[fd], buf);
		if (!save[fd])
			return (NULL);
	}
	line = trimline(save[fd]);
	save[fd] = restline(save[fd]);
	return (line);
}
