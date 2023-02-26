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
	int socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socketfd < 0)
	{
		std::cerr << "Socket::Fatal error" << std::endl;
		return (1);
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	memset(&addr.sin_zero, 0, 8);
	int ret = bind(socketfd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
	if (ret < 0)
	{
		std::cerr << "Bind::Fatal error" << std::endl;
		return (1);
	}
	ret = listen(socketfd, 1);
	if (ret < 0)
	{
		std::cerr << "Listen::Fatal error" << std::endl;
		return (1);
	}
	fd_set fdset;
	FD_ZERO(&fdset);
	FD_SET(socketfd, &fdset);
	struct timeval timeval;
	timeval.tv_sec = 1;
	timeval.tv_usec = 0;
	ret = select(0, &fdset, NULL, NULL, &timeval);
	if (ret < 0)
	{
		std::cerr << "Select::Fatal error" << std::endl;
		return (1);
	}
	return (0);
}