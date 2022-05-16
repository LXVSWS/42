/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:11:01 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/10 19:39:03 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	read_buffer(int fd, char **rest, char **buffer)
{
	size_t	nbytes;
	char	*tmprest;

	nbytes = 1;
	while (!(ft_strchr_nl(*rest)) && nbytes && g_exit_status != 130 \
	&& g_exit_status != 1)
	{
		nbytes = read(fd, *buffer, BUFFER_SIZE);
		(*buffer)[nbytes] = '\0';
		tmprest = *rest;
		*rest = ft_strjoin(*rest, *buffer);
		ft_free_ptr(tmprest);
	}
	ft_free_ptr(*buffer);
	return (nbytes);
}

static char	*set_lines(char **rest, char **line)
{
	size_t	lenrest;
	char	*tmprest;

	lenrest = 0;
	tmprest = *rest;
	while (((*rest)[lenrest] != '\0') && ((*rest)[lenrest] != '\n') \
	&& g_exit_status != 130 && g_exit_status != 1)
		lenrest++;
	if (ft_strchr_nl(*rest))
	{
		*line = ft_substr(*rest, 0, lenrest + 1);
		*rest = ft_strdup(*rest + lenrest + 1);
	}
	else
	{
		*line = ft_strdup(tmprest);
		*rest = NULL;
	}
	ft_free_ptr(tmprest);
	return (*line);
}

char	*ft_get_next_line_exit(int fd)
{
	size_t		nbytes;
	char		*line;
	char		*buffer;
	static char	*rest[MAX_FD];

	if (fd >= 0)
	{
		buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
		if (!buffer)
			return (NULL);
		if (read(fd, buffer, 0) < 0)
			return (ft_free_ptr(buffer));
		if (!rest[fd])
			rest[fd] = ft_strdup("");
		nbytes = read_buffer(fd, &rest[fd], &buffer);
		set_lines(&rest[fd], &line);
		if ((nbytes == 0) && (*line == '\0') && (g_exit_status != -2))
			return (ft_free_ptr(line));
		if (g_exit_status == 130 || g_exit_status == 1)
			return ("\0");
		return (line);
	}
	return (NULL);
}
