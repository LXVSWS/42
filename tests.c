#include "get_next_line/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main()
{
	int fd = open("gnl.txt", O_RDONLY);
	char *res = get_next_line(fd);
	while (res)
	{
		printf("%s", res);
		res = get_next_line(fd);
	}
}