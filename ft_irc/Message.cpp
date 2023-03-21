#include "Server.hpp"

void Server::message(Client* client, fd_set& fdset, std::vector<Client*>& clients, std::vector<Channel*>& channels)
{
	char buffer[513];
	memset(buffer, 0, sizeof(buffer));
	int bytes_recv = recv(client->fd, buffer, sizeof(buffer) - 1, 0);
	if (bytes_recv < 0)
		return ;
	else if (!bytes_recv)
		quit(client, fdset, clients, channels);
	else
	{
		//for (int i = 0 ; buffer[i] ; ++i)
		//	std::cout << buffer[i] << " : " << static_cast<int>(buffer[i]) << std::endl;
		std::vector<std::string> cmd = check(buffer);
		Command command(cmd, client, std::string(buffer));
		cmd = command.return_vector();
		//for (std::vector<std::string>::iterator it = cmd.begin() ; it != cmd.end() ; ++it)
		//	std::cout << "---" << *it << "---" << std::endl;
		if (cmd.empty())
			return ;
		if (cmd.front() == "QUIT")
			return (quit(client, fdset, clients, channels));
		int ret = handle(cmd, clients, client);
		if (ret <= 0 || ((cmd.front() == "PASS" || cmd.front() == "USER") && client->is_auth() == true))
			return ;
		if ((cmd.front() == "JOIN" || cmd.front() == "join") && client->is_auth() == true)
			join(cmd, client, channels);
		else if ((cmd.front() == "PRIVMSG" || cmd.front() == "NOTICE") && client->is_auth() == true)
			privmsg(cmd, client, clients, channels);
		else if (cmd.front() == "NICK" && client->is_auth() == true)
			nick(cmd, client, clients, channels);
		else if (cmd.front() == "KILL" && client->is_auth() == true)
			kill(cmd, client, fdset, clients, channels);
		else if (cmd.front() == "KICK" && client->is_auth() == true)
			kick(cmd, client, clients, channels);
		else if (cmd.front() == "MODE" && client->is_auth() == true)
			mode(&command, clients, channels, client);
		else if (cmd.front() == "TOPIC" && client->is_auth() == true)
			topic(&command, channels, client);
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
}

void Server::quit(Client* client, fd_set& fdset, std::vector<Client*>& clients, std::vector<Channel*>& channels)
{
	close(client->fd);
	FD_CLR(client->fd, &fdset);
	for (std::vector<Channel*>::iterator it = channels.begin() ; it != channels.end() ; ++it)
	{
		for (std::vector< ft::pair<std::string, int> >::iterator itt = (*it)->clients.begin() ; itt != (*it)->clients.end() ; ++itt)
			if (itt->first == client->nickname)
			{
				(*it)->clients.erase(itt);
				break;
			}
		for (std::vector<std::string>::iterator itt = (*it)->operators.begin() ; itt != (*it)->operators.end() ; ++itt)
			if (*itt == client->nickname)
			{
				(*it)->operators.erase(itt);
				break;
			}
		if ((*it)->clients.size() && (*it)->operators.empty())
		{
			(*it)->operators.push_back((*it)->clients.begin()->first);
			for (std::vector<Client*>::iterator i = clients.begin() ; i != clients.end() ; ++i)
				if ((*i)->nickname == (*it)->clients.begin()->first)
					(*i)->op.push_back((*it)->getName());
		}
		if ((*it)->clients.size())
			(*it)->send_userlist();
	}
	for (std::vector<Client*>::iterator it = clients.begin() ; it != clients.end() ; ++it)
		if (*it == client)
		{
			delete client;
			clients.erase(it);
			break;
		}
}

void Server::join(std::vector<std::string>& cmd, Client* client, std::vector<Channel*>& channels)
{
	if (cmd.size() < 2)
	{
		std::string str = ":ircserv NOTICE * :*** Not enough parameters\n";
		send(client->fd, str.data(), str.length(), 0);
		return ;
	}
	std::string channel = cmd.at(1);
	if ((channel.front() != '#' && channel.front() != '&') || channel.length() <= 1 || channel.length() > 200)
	{
		std::string str = ":ircserv NOTICE * :*** Channel must start with an # or & followed by 1-200 character(s)\n";
		send(client->fd, str.data(), str.length(), 0);
		return ;
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
			(*it)->setTopic("Bienvenue sur " + channel);
			for (std::vector< ft::pair<std::string, int> >::iterator itt = (*it)->clients.begin() ; itt != (*it)->clients.end() ; ++itt)
				if (itt->first == client->nickname)
					toggle = 1;
			if (!toggle)
			{
				toggle = 1;
				if ((*it)->operators.empty())
				{
					(*it)->operators.push_back(client->nickname);
					client->op.push_back(channel);
				}
				(*it)->clients.push_back(ft::make_pair<std::string, int>(client->nickname, client->fd));
				(*it)->send_userlist();
			}
			break;
		}
	if (!toggle)
	{
		Channel *new_channel;
		new_channel = new Channel(channel);
		new_channel->clients.push_back(ft::make_pair<std::string, int>(client->nickname, client->fd));
		new_channel->operators.push_back(client->nickname);
		channels.push_back(new_channel);
		client->op.push_back(channel);
		new_channel->send_userlist();
	}
}

void Server::privmsg(std::vector<std::string>& cmd, Client* client ,std::vector<Client*>& clients, std::vector<Channel*>& channels)
{
	if (cmd.size() < 3)
	{
		std::string str = ":ircserv NOTICE * :*** Not enough parameters\n";
		send(client->fd, str.data(), str.length(), 0);
		return ;
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

void Server::nick(std::vector<std::string>& cmd, Client* client, std::vector<Client*>& clients, std::vector<Channel*>& channels)
{
	if (cmd.size() < 2)
	{
		std::string str = ":ircserv NOTICE * :*** Not enough parameters\n";
		send(client->fd, str.data(), str.length(), 0);
		return ;
	}
	if (cmd.at(1).empty() || cmd.at(1).length() > 9)
	{
		std::string str = ":ircserv NOTICE * :*** Bad nickname\n";
		send(client->fd, str.data(), str.length(), 0);
		return ;
	}
	char toggle = 0;
	std::string dst = cmd.at(1);
	if (dst.front() == '#')
	{
		std::string str = ":ircserv NOTICE * :*** Nickname can't start with an #\n";
		send(client->fd, str.data(), str.length(), 0);
		return ;
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
		{
			for (std::vector< ft::pair<std::string, int> >::iterator itt = (*it)->clients.begin() ; itt != (*it)->clients.end() ; ++itt)
				if (itt->first == client->nickname)
				{
					itt->first = dst;
					break;
				}
			for (std::vector<std::string>::iterator itt = (*it)->operators.begin() ; itt != (*it)->operators.end() ; ++itt)
				if (*itt == client->nickname)
				{
					*itt = dst;
					break;
				}
			(*it)->send_userlist();
		}
		client->set_nickname(dst);
		send(client->fd, s.str().data(), s.str().length(), 0);
	}
}

void Server::kill(std::vector<std::string>& cmd, Client* client, fd_set& fdset, std::vector<Client*>& clients, std::vector<Channel*>& channels)
{
	if (cmd.size() < 3)
	{
		std::string str = ":ircserv NOTICE * :*** Not enough parameters\n";
		send(client->fd, str.data(), str.length(), 0);
		return ;
	}
	std::string usr = cmd.at(1);
	for (std::vector<Channel*>::iterator it = channels.begin() ; it != channels.end() ; ++it)
	{
		char toggle = 0;
		char toggle2 = 0;
		for (std::vector<std::string>::iterator itt = (*it)->operators.begin() ; itt != (*it)->operators.end() ; ++itt)
			if (*itt == client->nickname)
				toggle = 1;
		for (std::vector< ft::pair<std::string, int> >::iterator itt = (*it)->clients.begin() ; itt != (*it)->clients.end() ; ++itt)
			if (itt->first == usr)
				toggle2 = 1;
		if (toggle && toggle2)
		{
			for (std::vector<Client*>::iterator it = clients.begin() ; it != clients.end() ; ++it)
				if (usr == (*it)->nickname)
				{
					quit(*it, fdset, clients, channels);
					break;
				}
			if ((*it)->clients.size() && (*it)->operators.empty())
			{
				(*it)->operators.push_back((*it)->clients.begin()->first);
				for (std::vector<Client*>::iterator i = clients.begin() ; i != clients.end() ; ++i)
					if ((*i)->nickname == (*it)->clients.begin()->first)
						(*i)->op.push_back((*it)->getName());
			}
			if ((*it)->clients.size())
				(*it)->send_userlist();
			return ;
		}
	}
	std::string str = ":ircserv NOTICE * :*** Operation impossible\n";
	send(client->fd, str.data(), str.length(), 0);
}

void Server::kick(std::vector<std::string>& cmd, Client* client, std::vector<Client *>& clients, std::vector<Channel*>& channels)
{
	if (cmd.size() < 3)
	{
		std::string str = ":ircserv NOTICE * :*** Not enough parameters\n";
		send(client->fd, str.data(), str.length(), 0);
		return ;
	}
	std::string chan = cmd.at(1);
	std::string usr = cmd.at(2);
	for (std::vector<Channel*>::iterator it = channels.begin() ; it != channels.end() ; ++it)
		if ((*it)->getName() == chan)
		{
			char toggle = 0;
			for (std::vector<std::string>::iterator itt = (*it)->operators.begin() ; itt != (*it)->operators.end() ; ++itt)
				if (*itt == client->nickname)
					toggle = 1;
			if (toggle)
			{
				for (std::vector< ft::pair<std::string, int> >::iterator itt = (*it)->clients.begin() ; itt != (*it)->clients.end() ; ++itt)
					if (itt->first == usr)
					{
						std::stringstream ss;
						ss << ':' << itt->first << " PART :" << chan << '\n';
						send(itt->second, ss.str().data(), ss.str().length(), 0);
						(*it)->clients.erase(itt);
						break;
					}
				for (std::vector<std::string>::iterator itt = (*it)->operators.begin() ; itt != (*it)->operators.end() ; ++itt)
					if (*itt == usr)
					{
						(*it)->operators.erase(itt);
						break;
					}
				if ((*it)->clients.size() && (*it)->operators.empty())
				{
					(*it)->operators.push_back((*it)->clients.begin()->first);
					for (std::vector<Client*>::iterator i = clients.begin() ; i != clients.end() ; ++i)
						if ((*i)->nickname == (*it)->clients.begin()->first)
							(*i)->op.push_back((*it)->getName());
				}
				if ((*it)->clients.size())
					(*it)->send_userlist();
				return ;
			}
		}
	std::string str = ":ircserv NOTICE * :*** Operation impossible\n";
	send(client->fd, str.data(), str.length(), 0);
}
