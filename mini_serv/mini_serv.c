#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
// only for testing :
#include <fcntl.h>
#include <stdio.h>

void error_handler(char *str)
{
	write(2, str, strlen(str));
	exit(1);
}

int my_htons(int num)
{
	/*
	Extract the least significant byte of the input value using bitwise AND with 0xFF.
	Shift the least significant byte to the left by 8 bits to place it in the most significant byte position of the result.
	Extract the most significant byte of the input value using right shift and bitwise AND with 0xFF.
	Shift the most significant byte to the right by 8 bits to place it in the least significant byte position of the result.
	Combine the two bytes using bitwise OR.
	*/
	return (((num & 0xFF) << 8) | ((num >> 8) & 0xFF));
}

int main(int ac, char **av)
{
	if (ac < 2)
		error_handler("Wrong number of arguments\n");
	int port = atoi(av[1]); // port range : 1024-65535
	if (port <= 0)
		error_handler("Fatal error\n");
	int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd < 0)
		error_handler("Fatal error\n");
	//fcntl(sockfd, F_SETFL, O_NONBLOCK);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = my_htons(port);
	memset(&addr.sin_zero, 0, 8);
	int ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
	if (ret < 0)
	{
		close(sockfd);
		error_handler("Fatal error\n");
	}
	ret = listen(sockfd, 100);
	if (ret < 0)
	{
		close(sockfd);
		error_handler("Fatal error\n");
	}
	fd_set fdset;
	FD_ZERO(&fdset);
	FD_SET(sockfd, &fdset);
	struct timeval timeval;
	timeval.tv_sec = 5;
	timeval.tv_usec = 0;
	printf("Server up!\n");
	while (1)
	{
		fd_set copyset = fdset;
		ret = select(FD_SETSIZE, &copyset, NULL, NULL, &timeval);
		if (ret < 0)
		{
			close(sockfd);
			error_handler("Fatal error\n");
		}
		for (int i = 0 ; i < ret ; ++i)
		{
			if (FD_ISSET(sockfd, &copyset))
			{
				socklen_t len = sizeof(struct sockaddr);
				int client = accept(sockfd, NULL, &len);
				if (client < 0)
					continue;
				//fcntl(client, F_SETFL, O_NONBLOCK);
				FD_SET(client, &fdset);
				send(client, "Connected\n", 10, 0);
			}
		}
	}
	return (0);
}
