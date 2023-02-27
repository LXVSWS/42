#include "ircserv.hpp"

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr << "Wrong number of arguments" << std::endl;
		return (1);
	}
	int port = atoi(av[1]);
	if (port < 1024 || port > 65535)
		std::cout << "Careful, chosen port is out of range" << std::endl;
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
	int yes = 1;
	int ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
	if (ret < 0)
	{
		std::cerr << "Setsockopt::Fatal error" << std::endl;
		return (1);
	}
	ret = bind(sockfd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
	if (ret < 0)
	{
		std::cerr << "Bind::Fatal error" << std::endl;
		return (1);
	}
	ret = listen(sockfd, 5);
	if (ret < 0)
	{
		std::cerr << "Listen::Fatal error" << std::endl;
		return (1);
	}
	fd_set fdset;
	struct timeval timeval;
	timeval.tv_sec = 10;
	timeval.tv_usec = 0;
	std::cout << "Server up" << std::endl;
	while (1)
	{
		FD_ZERO(&fdset);
		FD_SET(sockfd, &fdset);
		ret = select(sockfd + 1, &fdset, NULL, NULL, &timeval);
		if (ret < 0)
		{
			std::cerr << "Select::Fatal error" << std::endl;
			return (1);
		}
		std::cout << ret << " connexion(s) detected" << std::endl;
		for (int i = 0 ; i < ret ; ++i)
		{
			if (FD_ISSET(sockfd, &fdset))
			{
				socklen_t len = sizeof(struct sockaddr);
				int client = accept(sockfd, NULL, &len);
				if (client < 0)
				{
					std::cerr << "Accept::Fatal error" << std::endl;
					return (1);
				}
				FD_SET(client, &fdset);
				int bytes_sent = send(client, "Connected!\n", 11, 0);
				if (bytes_sent != 11)
					std::cout << "Careful, the string is not fully sent" << std::endl;
			}
			else
				std::cout << "Other client" << std::endl;
		}
	}
	close(sockfd);
	return (0);
}
