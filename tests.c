#include "printf/ft_printf.h"
#include <fcntl.h>

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
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
	if (!s2)
		return (NULL);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == NULL)
		return (NULL);
	while (s1 && s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	return (str);
}

char	*get_next_line(int fd)
{
    static char *s;
	char *buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!buf)
        return (NULL);
    buf[BUFFER_SIZE] = 0;
	int i = 0;
    read(fd, buf, BUFFER_SIZE);
	s = ft_strjoin(s, buf);
    free(buf);
	return (s);
}

int	main()
{
	ft_printf("%s", get_next_line(open("file.txt", O_RDONLY)));
}
