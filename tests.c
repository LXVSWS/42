#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

size_t	ft_strlen(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s2 || !s1)
		return (NULL);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == NULL)
		return (NULL);
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char *line = "";
	char buf[BUFFER_SIZE + 1];
	int bytes_read = 0;
	if (fd < 0 || fd > 40 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (NULL);
	buf[bytes_read] = 0;
	*(ft_strchr(buf, '\n') + 1) = 0;
	line = ft_strjoin(line, buf);
	return (line);
}

int	main()
{
	for (int i = 0 ; i < 5 ; i++)
	{
		printf("%i:%s", i, get_next_line(open("gnl.txt", O_RDONLY)));
	}
}
