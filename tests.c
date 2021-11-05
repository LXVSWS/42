#include "printf/ft_printf.h"

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
    ft_printf("%s", get_next_line(1));
}
