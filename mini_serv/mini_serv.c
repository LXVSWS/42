#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

void error_handler(char *str)
{
	write(2, str, strlen(str));
	exit(1);
}

int main(int ac, char **av)
{
	if (ac < 2)
		error_handler("Wrong number of arguments\n");
	int port = atoi(av[1]);
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error_handler("Fatal error\n");
	struct sockaddr_in addr;
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(2130706433);
	addr.sin_port = htons(port);
	int ret = bind(sockfd, (const struct sockaddr*)&addr, sizeof(addr));
	if (ret < 0)
	{
		close(sockfd);
		error_handler("Fatal error\n");
	}
	ret = listen(sockfd, 10);
	if (ret < 0)
	{
		close(sockfd);
		error_handler("Fatal error\n");
	}
	fd_set fdset;
	FD_ZERO(&fdset);
	FD_SET(sockfd, &fdset);
	printf("Server up!\n");
	while (1)
	{
		fd_set copyset = fdset;
		ret = select(FD_SETSIZE, &copyset, NULL, NULL, NULL);
		if (ret < 0)
		{
			close(sockfd);
			error_handler("Fatal error\n");
		}
		for (int i = 0 ; i < ret ; ++i)
		{
			if (FD_ISSET(sockfd, &copyset))
			{
				struct sockaddr_in cli;
				socklen_t len = sizeof(struct sockaddr);
				int client = accept(sockfd, (struct sockaddr *)&cli, &len);
				if (client < 0)
					continue;
				FD_SET(client, &fdset);
				send(client, "Connected\n", 10, 0);
			}
		}
	}
	return (0);
}
