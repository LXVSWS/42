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
		std::cout << "Careful, chosen port is out of range (allowed ports : 1024 to 65535)" << std::endl;
	std::string password = av[2];
	int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd < 0)
	{
		std::cerr << "Socket::Fatal error" << std::endl;
		return (1);
	}
	int ret = fcntl(sockfd, F_SETFL, O_NONBLOCK);
	if (ret < 0)
	{
		std::cerr << "Fcntl::Fatal error" << std::endl;
		return (1);
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	memset(&addr.sin_zero, 0, 8);
	int yes = 1;
	ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
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
	FD_ZERO(&fdset);
	FD_SET(sockfd, &fdset);
	struct timeval timeval;
	timeval.tv_sec = 10;
	timeval.tv_usec = 0;
	std::vector<int> clients;
	std::cout << "Server up!" << std::endl;
	while (1)
	{
		fd_set copyset = fdset;
		ret = select(FD_SETSIZE, &copyset, NULL, NULL, &timeval);
		if (ret < 0)
		{
			std::cerr << "Select::Fatal error" << std::endl;
			return (1);
		}
		for (int i = 0 ; i < ret ; ++i)
		{
			if (FD_ISSET(sockfd, &copyset))
			{
				socklen_t len = sizeof(struct sockaddr);
				int client = accept(sockfd, NULL, &len);
				if (client < 0)
				{
					std::cerr << "Accept::Fatal error" << std::endl;
					return (1);
				}
				FD_SET(client, &fdset);
				clients.push_back(client);
				send(client, "Connected to the server!\n", 25, 0);
				std::stringstream ss;
				ss << "User " << client << " connected\n";
				std::cout << ss.str();
				for (std::vector<int>::iterator it = clients.begin() ; it != clients.end() ; ++it)
					if (*it != 0 && *it != client)
						send(*it, ss.str().data(), ss.str().length(), 0);
			}
			else
			{
				for (size_t i = 0 ; i < clients.size() ; ++i)
				{
					if (FD_ISSET(clients[i], &copyset))
					{
						int client = clients[i];
						char buffer[1024];
						memset(buffer, 0, 1024);
						int bytes_recv = recv(client, buffer, 1024, 0);
						if (bytes_recv <= 0)
						{
							close(client);
							FD_CLR(client, &fdset);
							clients[i] = 0;
							std::stringstream ss;
							ss << "User " << client << " disconnected\n";
							std::cout << ss.str();
							for (std::vector<int>::iterator it = clients.begin() ; it != clients.end() ; ++it)
								if (*it != 0 && *it != client)
									send(*it, ss.str().data(), ss.str().length(), 0);
						}
						else
						{
							std::stringstream ss;
							ss << "User " << client << " : " << buffer;
							std::cout << ss.str();
							for (std::vector<int>::iterator it = clients.begin() ; it != clients.end() ; ++it)
								if (*it != 0 && *it != client)
									send(*it, ss.str().data(), ss.str().length(), 0);
						}
					}
				}
			}
		}
	}
	close(sockfd);
	return (0);
}
