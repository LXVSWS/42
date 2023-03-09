#include "Server.hpp"

Server::Server(int port, std::string password) : port(port), password(password), sockfd(0)
{
	if (port < 1024 || port > 65535)
		std::cout << "Careful, chosen port is out of range (allowed ports : 1024 to 65535)" << std::endl;
}

int Server::init()
{
	int ret = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd < 0)
	{
		std::cerr << "Socket::Fatal error" << std::endl;
		return (-1);
	}
	sockfd = ret;
	ret = fcntl(sockfd, F_SETFL, O_NONBLOCK);
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
	return (0);
}

int Server::loop()
{
	fd_set fdset;
	FD_ZERO(&fdset);
	FD_SET(sockfd, &fdset);
	struct timeval timeval;
	timeval.tv_sec = 10;
	timeval.tv_usec = 0;
	std::vector<Client> clients;
	std::cout << "Server up!" << std::endl;
	while (1)
	{
		fd_set copyset = fdset;
		int ret = select(FD_SETSIZE, &copyset, NULL, NULL, &timeval);
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
				Client new_client(client);
				clients.push_back(new_client);
				std::string str = ":ircserv NOTICE * :*** Connected to the server\n";
				send(client, str.data(), str.length(), 0);
				std::stringstream ss;
				ss << "User " << client << " connected\n";
				std::cout << ss.str();
				for (std::vector<Client>::iterator it = clients.begin() ; it != clients.end() ; ++it)
					if (it->fd != 0 && it->fd != client)
						send(it->fd, ss.str().data(), ss.str().length(), 0);
			}
			else
			{
				for (size_t i = 0 ; i < clients.size() ; ++i)
				{
					if (FD_ISSET(clients[i].fd, &copyset))
					{
						int clientfd = clients[i].fd;
						char buffer[512];
						memset(buffer, 0, 512);
						int bytes_recv = recv(clientfd, buffer, 512, 0);
						if (bytes_recv <= 0)
						{
							close(clientfd);
							FD_CLR(clientfd, &fdset);
							clients[i] = 0;
							std::stringstream ss;
							ss << "User " << clientfd << " disconnected\n";
							std::cout << ss.str();
							for (std::vector<Client>::iterator it = clients.begin() ; it != clients.end() ; ++it)
								if (it->fd != 0 && it->fd != clientfd)
									send(it->fd, ss.str().data(), ss.str().length(), 0);
						}
						else
						{
							std::vector<std::string> cmd = check(buffer);
							ret = handle(cmd, clients[i]);
							if (ret <= 0)
								continue;
							std::stringstream ss;
							ss << "User " << clientfd << " : " << buffer;
							std::cout << ss.str();
							for (std::vector<Client>::iterator it = clients.begin() ; it != clients.end() ; ++it)
								if (it->fd != 0 && it->fd != clientfd)
									send(it->fd, ss.str().data(), ss.str().length(), 0);
						}
					}
				}
			}
		}
	}
}

std::vector<std::string> Server::check(char *buffer)
{
    std::vector<std::string> tokens;
    std::stringstream ss(buffer);
    std::string token;
    while (std::getline(ss, token, ' '))
		if (!token.size())
			continue;
		else
			tokens.push_back(token);
	return (tokens);
}

int Server::handle(std::vector<std::string> cmd, Client client)
{
	std::vector<std::string>::iterator it = cmd.begin();
	if (*it == "PASS")
	{
		++it;
		it->pop_back();
		if (*it != password)
		{
			client.toggle_password(false);
			std::string str = ":ircserv NOTICE * :*** Bad password\n";
			send(client.fd, str.data(), str.length(), 0);
			return (-1);
		}
		client.toggle_password(true);
	}
	else if (*it == "NICK")
	{
		++it;
		it->pop_back();
		if (it->empty() || (*it).length() > 9)
		{
			std::string str = ":ircserv NOTICE * :*** Bad nickname\n";
			send(client.fd, str.data(), str.length(), 0);
			return (-1);
		}
		client.set_nickname(*it);
	}
	else if (*it == "USER")
	{

	}
	else if (*it == "JOIN")
	{

	}
	else if (*it == "PRIVMSG")
	{

	}
	else
		return (1);
	return (0);
}
