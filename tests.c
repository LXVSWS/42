#include "printf/ft_printf.h"
#include <fcntl.h>

char	*get_next_line(int fd)
{
	static char buf[42];
    unsigned int count = 42;
    int bytes_read = read(fd, buf, count);
    (void)bytes_read;
	return (buf);
}


int	main()
{
	int fd = open("file.txt", O_RDONLY | O_CREAT);
    get_next_line(fd);
}
