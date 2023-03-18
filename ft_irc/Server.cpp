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
				std::string str = ":ircserv NOTICE * :*** Connected to the server\n";
				send(client, str.data(), str.length(), 0);
				std::string name = "guest";
				name.push_back(static_cast<char>(client + 48));
				std::cout << name << " connected" << std::endl;
			}
			else
			{
				for (size_t i = 0 ; i < clients.size() ; ++i)
				{
					if (FD_ISSET(clients[i]->fd, &copyset))
					{
						Client* client = clients[i];
						char buffer[513];
						memset(buffer, 0, sizeof(buffer));
						int bytes_recv = recv(client->fd, buffer, sizeof(buffer) - 1, 0);
						if (bytes_recv < 0)
							break;
						else if (!bytes_recv)
						{
							std::vector< ft::pair<std::string, std::string> > op;
							close(client->fd);
							FD_CLR(client->fd, &fdset);
							std::string name = "guest";
							name.push_back(static_cast<char>(client->fd + 48));
							if (!client->nickname.empty())
								name = client->nickname;
							for (std::vector<Channel*>::iterator it = channels.begin() ; it != channels.end() ; ++it)
								for (std::vector< ft::pair<std::string, int> >::iterator itt = (*it)->clients.begin() ; itt != (*it)->clients.end() ; ++itt)
									if (itt->first == client->nickname)
									{
										(*it)->clients.erase(itt);
										if ((*it)->clients.size())
										{
											ft::pair<std::string, std::string> tmp((*it)->send_userlist(), (*it)->getName());
											op.push_back(tmp);
										}
										break;
									}
							for (std::vector<Client*>::iterator it = clients.begin() ; it != clients.end() ; ++it)
								if (*it == client)
								{
									delete client;
									clients.erase(it);
									std::cout << name << " disconnected" << std::endl;
									break;
								}
							for (std::vector<Client*>::iterator it = clients.begin() ; it != clients.end() ; ++it)
								for (std::vector< ft::pair<std::string, std::string> >::iterator itt = op.begin() ; itt != op.end() ; ++itt)
									if ((*it)->nickname == itt->first)
										(*it)->op.push_back(itt->second);
						}
						else
						{
							//for (int i = 0 ; buffer[i] ; ++i)
							//	std::cout << buffer[i] << " : " << static_cast<int>(buffer[i]) << std::endl;
							std::vector<std::string> cmd = check(buffer);
							Command command(cmd, client, std::string(buffer));
							cmd = command.return_vector();
							//for (std::vector<std::string>::iterator it = cmd.begin() ; it != cmd.end() ; ++it)
							//	std::cout << "---" << *it << "---" << std::endl;
							if (cmd.empty() || cmd.front() == "QUIT" || cmd.front() == "MODE")
								break;
							ret = handle(cmd, clients, client);
							if (ret <= 0 || ((cmd.front() == "PASS" || cmd.front() == "USER") && client->is_auth() == true))
								break;
							if ((cmd.front() == "JOIN" || cmd.front() == "join") && client->is_auth() == true)
							{
								if (cmd.size() < 2)
								{
									std::string str = ":ircserv NOTICE * :*** Not enough parameters\n";
									send(client->fd, str.data(), str.length(), 0);
									break;
								}
								std::string channel = cmd.at(1);
								if ((channel.front() != '#' && channel.front() != '&') || channel.length() <= 1 || channel.length() > 200)
								{ // channel must not contain any virgule
									std::string str = ":ircserv NOTICE * :*** Channel must start with an # or & followed by 1-200 character(s)\n";
									send(client->fd, str.data(), str.length(), 0);
									break;
								}
								std::stringstream s;
								s << ":" << client->nickname << " JOIN :" << channel << '\n';
								send(client->fd, s.str().data(), s.str().length(), 0);
								std::stringstream str;
								str << ":ircserv 332 " << client->nickname << ' ' << channel << " :Bienvenue sur " << channel << '\n';
								send(client->fd, str.str().data(), str.str().length(), 0);
								char toggle = 0;
								for (std::vector<Channel*>::iterator it = channels.begin() ; it != channels.end() ; ++it)
									if (channel == (*it)->getName())
									{
										for (std::vector< ft::pair<std::string, int> >::iterator itt = (*it)->clients.begin() ; itt != (*it)->clients.end() ; ++itt)
											if (itt->first == client->nickname)
												toggle = 1;
										if (!toggle)
										{
											toggle = 1;
											(*it)->clients.push_back(ft::make_pair<std::string, int>(client->nickname, client->fd));
											if ((*it)->send_userlist() == client->nickname)
												client->op.push_back(channel);
										}
										break;
									}
								if (!toggle)
								{
									Channel *new_channel;
									new_channel = new Channel(channel);
									new_channel->clients.push_back(ft::make_pair<std::string, int>(client->nickname, client->fd));
									channels.push_back(new_channel);
									new_channel->send_userlist();
									client->op.push_back(channel);
								}
							}
							else if ((cmd.front() == "PRIVMSG" || cmd.front() == "NOTICE") && client->is_auth() == true)
							{
								if (cmd.size() < 3)
								{
									std::string str = ":ircserv NOTICE * :*** Not enough parameters\n";
									send(client->fd, str.data(), str.length(), 0);
									break;
								}
								char toggle = 0;
								std::string dst = cmd.at(1);
								std::stringstream ss;
								ss << ":" << client->nickname << ' ' << cmd.at(0) << ' ' << dst << ' ' << cmd.at(2) << '\n';
								if (dst.front() == '#')
								{
									for (std::vector<Channel*>::iterator it = channels.begin() ; it != channels.end() ; ++it)
										if (dst == (*it)->getName())
										{
											for (std::vector< ft::pair<std::string, int> >::iterator itt = (*it)->clients.begin() ; itt != (*it)->clients.end() ; ++itt)
												if (itt->first == client->nickname)
													toggle = 1;
											if (toggle)
												for (std::vector< ft::pair<std::string, int> >::iterator itt = (*it)->clients.begin() ; itt != (*it)->clients.end() ; ++itt)
													if (itt->first != client->nickname)
														send(itt->second, ss.str().data(), ss.str().length(), 0);
										}
								}
								else
								{
									for (std::vector<Client*>::iterator it = clients.begin() ; it != clients.end() ; ++it)
										if (dst == (*it)->nickname)
										{
											toggle = 1;
											send((*it)->fd, ss.str().data(), ss.str().length(), 0);
											break;
										}
								}
								if (!toggle && cmd.front() != "NOTICE")
								{
									std::string str = ":ircserv NOTICE * :*** You can't do this operation\n";
									send(client->fd, str.data(), str.length(), 0);
								}
							}
							else if (cmd.front() == "NICK" && client->is_auth() == true)
							{
								if (cmd.size() < 2)
								{
									std::string str = ":ircserv NOTICE * :*** Not enough parameters\n";
									send(client->fd, str.data(), str.length(), 0);
									break;
								}
								if (cmd.at(1).empty() || cmd.at(1).length() > 9)
								{
									std::string str = ":ircserv NOTICE * :*** Bad nickname\n";
									send(client->fd, str.data(), str.length(), 0);
									break;
								}
								char toggle = 0;
								std::string dst = cmd.at(1);
								if (dst.front() == '#')
								{
									std::string str = ":ircserv NOTICE * :*** Nickname can't start with an #\n";
									send(client->fd, str.data(), str.length(), 0);
									break;
								}
								for (size_t j = 0 ; j < clients.size() ; ++j)
									if (clients[j]->nickname == cmd.at(1))
									{
										toggle = 1;
										std::stringstream ss;
										ss << ":ircserv 436 " << clients[j]->nickname << " :Nickname collision KILL\n";
										send(client->fd, ss.str().data(), ss.str().length(), 0);
										break;
									}
								if (!toggle)
								{
									std::stringstream s;
									s << ":" << client->nickname << " NICK :" << dst << '\n';
									for (std::vector<Channel*>::iterator it = channels.begin() ; it != channels.end() ; ++it)
										for (std::vector< ft::pair<std::string, int> >::iterator itt = (*it)->clients.begin() ; itt != (*it)->clients.end() ; ++itt)
											if (itt->first == client->nickname)
											{
												itt->first = dst;
												(*it)->send_userlist();
												break;
											}
									client->set_nickname(dst);
									send(client->fd, s.str().data(), s.str().length(), 0);
								}
							}
							else
							{
								std::stringstream ss;
								if (client->is_auth() == false)
									ss << ":ircserv 451 * :You have not registered\n";
								else
									ss << ":ircserv 421 "<< client->nickname << ' ' << cmd.at(0) << " :Unknown command\n";
								send(client->fd, ss.str().data(), ss.str().length(), 0);
							}
						}
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
					ss << ":ircserv 436 " << clients[i]->nickname << " :Nickname collision KILL.\n";
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
