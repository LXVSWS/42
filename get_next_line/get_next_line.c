/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:25:22 by lwyss             #+#    #+#             */
/*   Updated: 2021/11/09 15:52:59 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*trimline(char *s)
{
	char *res;
	int	i = 0;

	while (s && s[i] && s[i] != '\n')
		i++;
	res = malloc(sizeof(char) * (i + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (s && s[i] && s[i] != '\n')
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\n';
	res[++i] = 0;
	return (res);
}

char	*restline(char *s)
{
	char *res;
	int	i = 0;
	int j = 0;

	while (s && s[i] && s[i] != '\n')
		i++;
	res = malloc(sizeof(char) * (ft_strlen(s) - i + 1));
	if (!res)
		return (NULL);
	while (s && s[i])
		res[j++] = s[++i];
	res[j] = 0;
	return (res);
}

char	*get_next_line(int fd)
{
	static char *save = NULL;
	char buf[BUFFER_SIZE + 1];
	int bytes_read = BUFFER_SIZE;
	char *tmp = NULL;
	char *line = NULL;
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	while (bytes_read)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		buf[bytes_read] = 0;
		tmp = save;
		save = ft_strjoin(tmp, buf);
		free(tmp);
		if (ft_strchr(save, '\n'))
		{
			line = trimline(save);
			tmp = save;
			save = restline(tmp);
			free(tmp);
			break;
		}
		if (!bytes_read && !ft_strchr(save, '\n'))
			free(save);
		if (!save)
			return (NULL);
	}
	return (line);
}
