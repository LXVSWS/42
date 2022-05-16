/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:11:01 by rahmed            #+#    #+#             */
/*   Updated: 2021/12/10 21:30:00 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	read_buffer(int fd, char **rest, char **buffer)
{
	size_t	nbytes;
	char	*tmprest;

	nbytes = 1;
	while (!(ft_strchr_nl(*rest)) && nbytes)
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
	while (((*rest)[lenrest] != '\0') && ((*rest)[lenrest] != '\n'))
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

char	*ft_get_next_line(int fd)
{
	size_t		nbytes;
	char		*line;
	char		*buffer;
	static char	*rest[MAX_FD];

	if ((BUFFER_SIZE > 0) && (fd >= 0))
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
		if ((nbytes == 0) && (*line == '\0'))
			return (ft_free_ptr(line));
		return (line);
	}
	return (NULL);
}
