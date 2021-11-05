#include "printf/ft_printf.h"
#include <fcntl.h>

static char	*ft_strjoin(char const *s1, char const *s2)
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

char	*get_next_line(int fd)
{
	static char *s = "";
	char buf[BUFFER_SIZE];
    while (read(fd, buf, BUFFER_SIZE))
		ft_strjoin(s, buf);
	return (s);
}

int	main()
{
	int fd = open("file.txt", O_RDONLY);
	char *s = get_next_line(fd);
	ft_printf("%s", s); 
	while (s)
		ft_printf("%s", get_next_line(fd));
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
