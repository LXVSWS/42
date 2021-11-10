/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:25:22 by lwyss             #+#    #+#             */
/*   Updated: 2021/11/10 01:06:25 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*trimline(char *s)
{
	char *res;
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	if (s[i])
		res = malloc(sizeof(char) * (i + 2));
	else
		res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s && s[i] && s[i] != '\n')
	{
		res[i] = s[i];
		i++;
	}
	if (s[i])
		res[i++] = '\n';
	res[i] = 0;
	return (res);
}

char	*restline(char *s)
{
	char *res;
	int	i = 0;
	int j = 0;

	while (s && s[i] && s[i] != '\n')
		i++;
	if (!s[i])
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(s) - i + 1));
	if (!res)
		return (NULL);
	while (s[i])
		res[j++] = s[++i];
	res[j] = 0;
	free(s);
	return (res);
}

char	*get_next_line(int fd)
{
	static char *save = NULL;
	char buf[BUFFER_SIZE + 1];
	int bytes_read = 1;
	char *line = NULL;
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	while (bytes_read && !ft_strchr(save, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		buf[bytes_read] = 0;
		if (bytes_read)
			save = ft_strjoin(save, buf);
	}
	if (ft_strchr(save, '\n'))
	{
		line = trimline(save);
		save = restline(save);
		return (line);
	}
	free(save);
	if (!bytes_read && !save)
		return (NULL);
	return (line);
}
