#include "get_next_line.h"

char    *readline(char *save, int fd)
{
    char    *buf;
    int     bytes_read;

    bytes_read = 1;
    buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buf)
        return (NULL);
    while (bytes_read && !ft_strchr(save, '\n'))
    {
        bytes_read = read(fd, buf, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(buf);
            return (NULL);
        }
        buf[bytes_read] = 0;
        save = ft_strjoin(save, buf);
    }
    free(buf);
    return (save);
}

char    *trimline(char *save)
{
    char    *line;
    size_t  i;

    i = 0;
    if (!save[i])
        return (NULL);
    while (save[i] && save[i] != '\n')
        i++;
    if (save[i] != '\n')
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

char    *restline(char *save)
{
    char    *line;
    size_t  i;
    size_t  j;

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

char    *get_next_line(int fd)
{
    static char *save;
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
    save = readline(save, fd);
    if (!save)
        return (NULL);
    line = trimline(save);
    save = restline(save);
    return (line);
}