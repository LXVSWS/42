#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	buf[BUFFER_SIZE] = 0;
	int bytes_read = 1;
	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read != BUFFER_SIZE)
		(void)fd;
	return (buf);
}

int	main()
{
	for (int i = 0 ; i < 10 ; i++)
		printf("%i:%s\n", i, get_next_line(open("gnl.txt", O_RDONLY)));
}
