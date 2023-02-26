#include "ircserv.hpp"

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr << "Wrong number of arguments" << std::endl;
		return (1);
	}
	int port = atoi(av[1]);
	std::string password = av[2];
	int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd < 0)
	{
		std::cerr << "Socket::Fatal error" << std::endl;
		return (1);
	}
	fcntl(sockfd, F_SETFL, O_NONBLOCK);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	memset(&addr.sin_zero, 0, 8);
	int ret = bind(sockfd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
	if (ret < 0)
	{
		std::cerr << "Bind::Fatal error" << std::endl;
		return (1);
	}
	ret = listen(sockfd, 1);
	if (ret < 0)
	{
		std::cerr << "Listen::Fatal error" << std::endl;
		return (1);
	}
	fd_set fdset;
	struct timeval timeval;
	timeval.tv_sec = 10;
	timeval.tv_usec = 0;
	int maxfd = sockfd + 1;
	std::cout << "Server up" << std::endl;
	while (1)
	{
		FD_ZERO(&fdset);
		FD_SET(sockfd, &fdset);
		ret = select(maxfd, &fdset, NULL, NULL, &timeval);
		if (ret < 0)
		{
			std::cerr << "Select::Fatal error" << std::endl;
			return (1);
		}
		if (FD_ISSET(sockfd, &fdset))
		{
			std::cout << ret << " connexion detected" << std::endl;
			socklen_t len = sizeof(struct sockaddr);
			int client = accept(sockfd, NULL, &len);
			send(client, "Connected!\n", 11, 0);
		}
	}
	return (0);
}
