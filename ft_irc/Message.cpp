#include "Server.hpp"

void Server::message(Client* client, fd_set& fdset, std::vector<Client*>& clients, std::vector<Channel*>& channels)
{
	char buffer[513];
	memset(buffer, 0, sizeof(buffer));
	int bytes_recv = recv(client->fd, buffer, sizeof(buffer) - 1, 0);
	if (bytes_recv < 0)
		return ;
	else if (!bytes_recv)
		quit(client, fdset, clients, channels, "Timeout");
	else
	{
		std::vector<std::string> cmd = check(buffer);
		Command command(cmd, client, std::string(buffer));
		cmd = command.return_vector();
		if (cmd.empty())
			return ;
		if (cmd.front() == "QUIT")
			return (quit(client, fdset, clients, channels, cmd.back()));
		int ret = handle(cmd, clients, client);
		if (ret <= 0 || ((cmd.front() == "PASS" || cmd.front() == "USER") && client->is_auth() == true))
			return ;
		if (cmd.front() == "JOIN" && client->is_auth() == true)
			join(cmd, client, channels);
		else if ((cmd.front() == "PRIVMSG" || cmd.front() == "NOTICE") && client->is_auth() == true)
			privmsg(cmd, client, clients, channels);
		else if (cmd.front() == "NICK" && client->is_auth() == true)
			nick(cmd, client, clients, channels);
		else if (cmd.front() == "KILL" && client->is_auth() == true)
			kill(cmd, client, fdset, clients, channels);
		else if (cmd.front() == "KICK" && client->is_auth() == true)
			kick(cmd, client, clients, channels);
		else if (cmd.front() == "PART" && client->is_auth() == true)
			part(cmd, client, clients, channels);
		else if (cmd.front() == "MODE" && client->is_auth() == true)
			mode(&command, clients, channels, client);
		else if (cmd.front() == "TOPIC" && client->is_auth() == true)
			topic(&command, channels, client);
		else if (cmd.front() == "INVITE" && client->is_auth() == true)
			invite(cmd, clients, client, channels);
		else
		{
			std::stringstream ss;
			if (client->is_auth() == false)
				ss << ":ircserv 451 :You have not registered\n";
			else
				ss << ":ircserv 421 " << client->nickname << ' ' << cmd.at(0) << " :Unknown command\n";
			send(client->fd, ss.str().data(), ss.str().length(), 0);
		}
	}
}

void Server::quit(Client* client, fd_set& fdset, std::vector<Client*>& clients, std::vector<Channel*>& channels, std::string msg)
{
	close(client->fd);
	FD_CLR(client->fd, &fdset);
	for (std::vector<Channel*>::iterator it = channels.begin() ; it != channels.end() ; ++it)
	{
		char toggle = 0;
		for (std::vector< ft::pair<std::string, int> >::iterator itt = (*it)->clients.begin() ; itt != (*it)->clients.end() ; ++itt)
			if (itt->first == client->nickname)
			{
				(*it)->clients.erase(itt);
				toggle = 1;
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
		if (toggle)
		{
			std::stringstream s;
			if (msg.front() == ':')
				msg.erase(msg.begin());
			s << ":" << client->nickname << " QUIT :" << msg << '\n';
			for (std::vector<Client*>::iterator i = clients.begin() ; i != clients.end() ; ++i)
				if ((*i)->nickname != client->nickname)
					send((*i)->fd, s.str().data(), s.str().length(), 0);
			(*it)->send_userlist();
		}
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
    	std::string str = ":ircserv 461 :Not enough parameters\n";
		send(client->fd, str.data(), str.length(), 0);
		return ;
	}
	std::string channel = cmd.back();
	while (channel != cmd.front())
	{
		if ((channel.front() != '#' && channel.front() != '&') || channel.length() <= 1 || channel.length() > 200)
		{
			cmd.pop_back();
			channel = cmd.back();
			continue;
		}
		std::stringstream s;
		s << ":" << client->nickname << " JOIN :" << channel << '\n';
		std::stringstream str;
		str << ":ircserv 332 " << client->nickname << ' ' << channel << " :Bienvenue sur " << channel << '\n';
		char toggle = 0;
		for (std::vector<Channel*>::iterator it = channels.begin() ; it != channels.end() ; ++it)
			if (channel == (*it)->getName())
			{
				for (std::vector< ft::pair<std::string, int> >::iterator itt = (*it)->clients.begin() ; itt != (*it)->clients.end() ; ++itt)
					if (itt->first == client->nickname)
					{
						std::stringstream ss;
						ss << ":ircserv NOTICE " << client->nickname << " :You are already on this channel\n";
						send(client->fd, ss.str().data(), ss.str().length(), 0);
						toggle = 1;
						break;
					}
				if (toggle)
				{
					toggle = 0;
					continue;
				}
				toggle = 1;
				send(client->fd, s.str().data(), s.str().length(), 0);
				send(client->fd, str.str().data(), str.str().length(), 0);
				if ((*it)->operators.empty())
				{
					(*it)->operators.push_back(client->nickname);
					client->op.push_back(channel);
				}
				for (std::vector< ft::pair<std::string, int> >::iterator itt = (*it)->clients.begin() ; itt != (*it)->clients.end() ; ++itt)
					send(itt->second, s.str().data(), s.str().length(), 0);
				(*it)->clients.push_back(ft::make_pair<std::string, int>(client->nickname, client->fd));
				(*it)->send_userlist();
			}
		if (!toggle)
		{
			Channel *new_channel;
			new_channel = new Channel(channel);
			new_channel->clients.push_back(ft::make_pair<std::string, int>(client->nickname, client->fd));
			new_channel->operators.push_back(client->nickname);
			new_channel->setTopic("Bienvenue sur " + channel);
			channels.push_back(new_channel);
			client->op.push_back(channel);
			send(client->fd, s.str().data(), s.str().length(), 0);
			send(client->fd, str.str().data(), str.str().length(), 0);
			new_channel->send_userlist();
		}
		cmd.pop_back();
		channel = cmd.back();
	}
}

void Server::privmsg(std::vector<std::string>& cmd, Client* client ,std::vector<Client*>& clients, std::vector<Channel*>& channels)
{
	if (cmd.size() < 3)
	{
        std::string str = ":ircserv 461 :Not enough parameters\n";
		send(client->fd, str.data(), str.length(), 0);
		return ;
	}
	std::string txt = cmd.back();
	cmd.pop_back();
	std::string dst = cmd.back();
	if (txt == "!bot" || txt == "!BOT")
	{
		std::string s = ":BOT PRIVMSG " + dst + " 🤖\n";
		send(client->fd, s.data(), s.length(), 0);
		return ;
	}
	while (dst != cmd.front())
	{
		char toggle = 0;
		std::stringstream ss;
		ss << ":" << client->nickname << ' ' << cmd.at(0) << ' ' << dst << ' ' << txt << '\n';
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
			std::string str = ":ircserv 401 " + client->nickname + " " + dst + " :No such nick/channel\n";
			send(client->fd, str.data(), str.length(), 0);
		}
		cmd.pop_back();
		dst = cmd.back();
	}
}

void Server::nick(std::vector<std::string>& cmd, Client* client, std::vector<Client*>& clients, std::vector<Channel*>& channels)
{
	if (cmd.size() < 2)
	{
        std::string str = ":ircserv 461 :Not enough parameters\n";
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
			std::stringstream s;
			s << ":" << client->nickname << " NICK :" << dst << '\n';
			for (std::vector<Client*>::iterator i = clients.begin() ; i != clients.end() ; ++i)
				send((*i)->fd, s.str().data(), s.str().length(), 0);
			(*it)->send_userlist();
		}
		client->set_nickname(dst);
	}
}

void Server::kill(std::vector<std::string>& cmd, Client* client, fd_set& fdset, std::vector<Client*>& clients, std::vector<Channel*>& channels)
{
	if (cmd.size() < 3)
	{
        std::string str = ":ircserv 461 :Not enough parameters\n";
		send(client->fd, str.data(), str.length(), 0);
		return ;
	}
	std::string usr = cmd.at(1);
	std::string comm = cmd.at(2);
	if (comm.front() == ':')
		comm.erase(comm.begin());
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
			for (std::vector<Client*>::iterator itt = clients.begin() ; itt != clients.end() ; ++itt)
				if (usr == (*itt)->nickname)
				{
					std::stringstream ss;
					ss << ':' << client->nickname << " KILL :" << comm << '\n';
					send((*itt)->fd, ss.str().data(), ss.str().length(), 0);
					quit(*itt, fdset, clients, channels, comm);
					break;
				}
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
		std::string str = ":ircserv 461 :Not enough parameters\n";
		send(client->fd, str.data(), str.length(), 0);
		return ;
	}
	std::vector<std::string> chan;
	std::vector<std::string> usr;
	std::string comm = "";
	if (cmd.back() != ",")
	{
		comm = cmd.back();
		if (comm.front() == ':')
			comm.erase(comm.begin());
		cmd.pop_back();
	}
	while (cmd.back() == ",")
		cmd.pop_back();
	while (cmd.back() != ",")
	{
		usr.push_back(cmd.back());
		cmd.pop_back();
	}
	while (cmd.back() == ",")
		cmd.pop_back();
	while (cmd.back() != cmd.front())
	{
		chan.push_back(cmd.back());
		cmd.pop_back();
	}
	for (std::vector<std::string>::iterator iter = chan.begin() ; iter != chan.end() ; ++iter)
		for (std::vector<std::string>::iterator ite = usr.begin() ; ite != usr.end() ; ++ite)
			for (std::vector<Channel*>::iterator it = channels.begin() ; it != channels.end() ; ++it)
				if ((*it)->getName() == *iter)
				{
					char toggle = 0;
					char toggle2 = 0;
					for (std::vector<std::string>::iterator itt = (*it)->operators.begin() ; itt != (*it)->operators.end() ; ++itt)
						if (*itt == client->nickname)
							toggle = 1;
					if (!toggle)
					{
						std::string str = ":ircserv 482 " + client->nickname + " " + (*it)->getName() + " :You're not channel operator\n";
						send(client->fd, str.data(), str.length(), 0);
						break;
					}
					for (std::vector< ft::pair<std::string, int> >::iterator itt = (*it)->clients.begin() ; itt != (*it)->clients.end() ; ++itt)
						if (itt->first == *ite)
							toggle2 = 1;
					if (toggle && toggle2)
					{
						toggle = 0;
						for (std::vector< ft::pair<std::string, int> >::iterator itt = (*it)->clients.begin() ; itt != (*it)->clients.end() ; ++itt)
							if (itt->first == *ite)
							{
								std::stringstream ss;
								ss << ':' << itt->first << " PART " << *iter << " :" << comm << '\n';
								send(itt->second, ss.str().data(), ss.str().length(), 0);
								std::string str = ":ircserv NOTICE * :*** Kicked of " + *iter + " ! Reason : " + comm + "\n";
								send(itt->second, str.data(), str.length(), 0);
								(*it)->clients.erase(itt);
								toggle = 1;
								break;
							}
						for (std::vector<std::string>::iterator itt = (*it)->operators.begin() ; itt != (*it)->operators.end() ; ++itt)
							if (*itt == *ite)
							{
								(*it)->operators.erase(itt);
								break;
							}
						for (std::vector<Client*>::iterator i = clients.begin() ; i != clients.end() ; ++i)
							if ((*i)->nickname == *ite)
								for (std::vector<std::string>::iterator j = (*i)->op.begin() ; j != (*i)->op.end() ; ++j)
									if (*j == (*it)->getName())
										{
											(*i)->op.erase(j);
											break;
										}
						if ((*it)->clients.size() && (*it)->operators.empty())
						{
							(*it)->operators.push_back((*it)->clients.begin()->first);
							for (std::vector<Client*>::iterator i = clients.begin() ; i != clients.end() ; ++i)
								if ((*i)->nickname == (*it)->clients.begin()->first)
									(*i)->op.push_back((*it)->getName());
						}
						if (toggle)
						{
							std::stringstream s;
							s << ':' << client->nickname << " KICK " << *iter << ' ' << *ite << " :" << comm << '\n';
							for (std::vector<Client*>::iterator i = clients.begin() ; i != clients.end() ; ++i)
								send((*i)->fd, s.str().data(), s.str().length(), 0);
							(*it)->send_userlist();
						}
					}
				}
}

void Server::part(std::vector<std::string>& cmd, Client* client, std::vector<Client *>& clients, std::vector<Channel*>& channels)
{
	if (cmd.size() < 2)
	{
        std::string str = ":ircserv 461 :Not enough parameters\n";
		send(client->fd, str.data(), str.length(), 0);
		return ;
	}
	std::string channel = cmd.back();
	while (channel != cmd.front())
	{
		if ((channel.front() != '#' && channel.front() != '&') || channel.length() <= 1 || channel.length() > 200)
		{
			cmd.pop_back();
			channel = cmd.back();
			continue;
		}
		std::stringstream s;
		s << ':' << client->nickname << " PART " << channel << " :Bye\n";
		send(client->fd, s.str().data(), s.str().length(), 0);
		for (std::vector<Channel*>::iterator it = channels.begin() ; it != channels.end() ; ++it)
			if (channel == (*it)->getName())
			{
				char toggle = 0;
				for (std::vector< ft::pair<std::string, int> >::iterator itt = (*it)->clients.begin() ; itt != (*it)->clients.end() ; ++itt)
					if (itt->first == client->nickname)
					{
						(*it)->clients.erase(itt);
						toggle = 1;
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
				if (toggle)
				{
					std::stringstream s;
					s << ':' << client->nickname << " PART " << channel << " :Bye\n";
					for (std::vector<Client*>::iterator i = clients.begin() ; i != clients.end() ; ++i)
						if ((*i)->nickname != client->nickname)
							send((*i)->fd, s.str().data(), s.str().length(), 0);
					(*it)->send_userlist();
				}
			}
		cmd.pop_back();
		channel = cmd.back();
	}
}
