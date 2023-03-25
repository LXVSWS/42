#include "Server.hpp"

Server::Server(int port, std::string password) : port(port), sockfd(0), password(password)
{
	if (port < 1024 || port > 65535)
	{
		std::cout << "Careful, chosen port is out of range (allowed ports : 1024 to 65535)" << std::endl;
		exit(1);
	}
}

Server::~Server()
{
	if (sockfd)
		close(sockfd);
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
	ret = listen(sockfd, 100);
	if (ret < 0)
	{
		std::cerr << "Listen::Fatal error" << std::endl;
		return (1);
	}
	signal(SIGPIPE, SIG_IGN);
	return (0);
}

void Server::loop()
{
	fd_set fdset;
	FD_ZERO(&fdset);
	FD_SET(sockfd, &fdset);
	struct timeval timeval;
	timeval.tv_sec = 5;
	timeval.tv_usec = 0;
	std::vector<Client*> clients;
	std::vector<Channel*> channels;
	std::cout << "Server up!" << std::endl;
	while (1)
	{
		fd_set copyset = fdset;
		int ret = select(FD_SETSIZE, &copyset, NULL, NULL, &timeval);
		if (ret < 0)
		{
			std::cerr << "Select::Fatal error" << std::endl;
			return ;
		}
		for (int i = 0 ; i < ret ; ++i)
		{
			if (FD_ISSET(sockfd, &copyset))
			{
				socklen_t len = sizeof(struct sockaddr);
				int client = accept(sockfd, NULL, &len);
				if (client < 0)
					continue;
				ret = fcntl(client, F_SETFL, O_NONBLOCK);
				if (ret < 0)
					continue;
				FD_SET(client, &fdset);
				Client* new_client;
				new_client = new Client(client);
				clients.push_back(new_client);
				std::string str = ":ircserv NOTICE * :Connected to the server, checking ident...\n";
				send(client, str.data(), str.length(), 0);
			}
			else
			{
				for (size_t i = 0 ; i < clients.size() ; ++i)
				{
					if (FD_ISSET(clients[i]->fd, &copyset))
					{
						message(clients[i], fdset, clients, channels);
						break;
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
	char toggle = 0;
    while (std::getline(ss, token, ' '))
	{
		if (!token.size() || token == "\r\n")
			continue;
		for (size_t i = 0 ; i < token.length() ; ++i)
			if (token.at(i) == '\r' && token.at(i + 1) == '\n')
			{
				tokens.push_back(token.substr(0, i));
				std::string str = token.substr(i + 2);
				if (!str.empty() && str.front() != '\n')
					tokens.push_back(str);
				toggle = 1;
				break;
			}
		if (!toggle)
			tokens.push_back(token);
		else
			toggle = 0;
	}
	return (tokens);
}

int Server::handle(std::vector<std::string> cmd, std::vector<Client*> clients, Client* client)
{
	if (client->is_auth() == true)
		return (1);
	for (std::vector<std::string>::iterator it = cmd.begin() ; it != cmd.end() ; ++it)
	{
		if (*it == "CAP" || *it == "LS" || *it == "302")
			continue;
		if (*it == "PASS")
		{
			if (++it == cmd.end())
				break;
			if (*it != password)
			{
				client->toggle_password(false);
				break;
			}
			if (*it == password)
				client->toggle_password(true);
			continue;
		}
		if (*it == "NICK")
		{
			if (++it == cmd.end())
				break;
			if (it->empty() || (*it).length() > 9)
				break;
			for (size_t i = 0 ; i < clients.size() ; ++i)
				if (clients[i]->nickname == *it)
				{
					std::stringstream ss;
					ss << ":ircserv 436 " << clients[i]->nickname << " :Nickname collision KILL\n";
					send(client->fd, ss.str().data(), ss.str().length(), 0);
					return (-1);
				}
			client->set_nickname(*it);
			continue;
		}
		if (*it == "USER")
		{
			if (++it == cmd.end())
				break;
			if (it->empty() || (*it).length() > 9)
				break;
			client->set_username(*it);
			if (++it == cmd.end())
				break;
			if (it->empty() || (*it).length() > 9)
				break;
			client->set_hostname(*it);
			if (++it == cmd.end())
				break;
			if (it->empty() || (*it).length() > 9)
				break;
			client->set_servername(*it);
			if (++it == cmd.end())
				break;
			if (it->empty() || it->front() == '\r' || it->front() == '\n')
				break;
			client->set_realname(*it);
			continue;
		}
		if (it == cmd.begin())
			return (1);
	}
	if (client->is_auth() == false)
		client->authentification();
	return (0);
}
