#include "get_next_line/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main()
{
	int fd = open("gnl.txt", O_RDONLY);
	int fd2 = open("readme.md", O_RDONLY);
	char *res = get_next_line(fd);
	if (!res)
		printf("res NULL");
	char *res2 = get_next_line(fd2);
	if (!res2)
		printf("res2 NULL");
	while (res || res2)
	{
		printf("%s", res);
		res = get_next_line(fd);
		printf("%s", res2);
		res2 = get_next_line(fd2);
	}
}
