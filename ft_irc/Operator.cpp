#include "Server.hpp"

int	Server::mode(Command *command, std::vector<Client*> clients, std::vector<Channel*> channels, Client *client)
{
    if (command->command.size() == 2)
    {
        command->command.clear();
        command->command.push_back("MODE");
        return (1);
    }
    if (command->command.size() < 4)
    {
        command->command.clear();
        command->command.push_back("MODE");
        std::string str = ":ircserv 461 :Not enough parameters\n";
        send(client->fd, str.data(), str.length(), 0);
        return (1);
    }
    int rights = 0;
    int push = 1;
    for (std::vector<std::string>::iterator itt = client->op.begin(); itt != client->op.end(); ++itt)
        if ((*itt) == command->command[1])
            rights = 1;
    if (rights == 0)
    {
        std::string str = ":ircserv 482 " + command->command[3] + " " + command->command[1] + " :You're not channel operator\n";
        send(client->fd, str.data(), str.length(), 0);
        return (1);
    }
    if (command->o_mode == true && rights == 1)
    {
        for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
        {
            if ((*it)->nickname == command->command[3])
            {
                for (std::vector<std::string>::iterator itt = (*it)->op.begin(); itt != (*it)->op.end(); ++itt)
                {
                    if ((*itt) == command->command[1])
                    {
                        push = 0;
                        break;
                    }
                }
                if (push)
                {
                    (*it)->op.push_back(command->command[1]);
                    for (std::vector<Channel *>::iterator i = channels.begin(); i != channels.end(); ++i)
                    {
                        if ((*i)->getName() == command->command[1])
                        {
                            (*i)->operators.push_back(command->command[3]);
                            (*i)->send_userlist();
                            break;
                        }
                    }
                }
            }
        }
    }
    else if (command->o_mode == false && rights == 1)
    {
        for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
        {
            if ((*it)->nickname == command->command[3])
            {
                for (std::vector<std::string>::iterator itt = (*it)->op.begin(); itt != (*it)->op.end(); ++itt)
                    if ((*itt) == command->command[1])
                    {
                        (*it)->op.erase(itt);
                        break ;
                    }
            }
        }
        for (std::vector<Channel *>::iterator i = channels.begin(); i != channels.end(); ++i)
        {
            if ((*i)->getName() == command->command[1])
            {
                for(std::vector<std::string>::iterator j = (*i)->operators.begin(); j != (*i)->operators.end(); j++)
                    if ((*j) == command->command[3])
                    {
                        (*i)->operators.erase(j);
                        (*i)->send_userlist();
                        break ;
                    }
            }
        }
    }
    return (0);
}


int	Server::topic(Command *command, std::vector<Channel*> channels, Client *client)
{
    if (command->command.size() < 2)
    {
        std::string str = ":ircserv 461 :Not enough parameters\n";
        send(client->fd, str.data(), str.length(), 0);
        return (1);
    }
    int rights = 0;
    for (std::vector<std::string>::iterator itt = client->op.begin(); itt != client->op.end(); ++itt)
        if ((*itt) == command->command[1])
            rights = 1;
    if (!rights && command->command.size() == 3)
    {
        std::string str = ":ircserv 482 " + command->command[1] + " :You're not channel operator\n";
        send(client->fd, str.data(), str.length(), 0);
        return (1);
    }
    int check = 0;
    for (std::vector<Channel*>::iterator i = channels.begin(); i != channels.end(); ++i)
        if ((*i)->getName() == command->command[1])
            check = 1;
    if (check == 1)
    {
        if (command->command.size() == 2)
        {
            for (std::vector<Channel*>::iterator i = channels.begin(); i != channels.end(); ++i)
            {
                if ((*i)->getName() == command->command[1])
                {
                    if ((*i)->getTopic().size() > 0)
                    {
                        std::string str = ":ircserv 332 " + client->nickname + " " + (*i)->getName() + " :" + (*i)->getTopic() + "\n" ;
                        send(client->fd, str.data(), str.length(), 0);
                        return (1);
                    }
                    else
                    {
                        std::string str = ":ircserv 331 " + (*i)->getName() + " :No topic is set\n";
                        send(client->fd, str.data(), str.length(), 0);
                        return (1);
                    }
                }
            }
        }
		if (command->command.size() == 3)
		{
            for (std::vector<Channel*>::iterator i = channels.begin(); i != channels.end(); ++i)
            if ((*i)->getName() == command->command[1])
            {
                if (command->command[2][0] == ':')
                {
                    std::string reforge;
                    reforge = command->command[2].erase(0, 1);
                    (*i)->setTopic(reforge);
                }
                else
                    (*i)->setTopic(command->command[2]);

            }
		}
    }
    else
    {
        std::string str = ":ircserv 403 " + client->nickname + " " + command->command[1] + " :No such channel\n";
        send(client->fd, str.data(), str.length(), 0);
        return (1);
    }
    return (0);
}

void	Server::invite(std::vector<std::string>& cmd,std::vector<Client*>& clients, Client* client,std::vector<Channel*>& channels)
{
	int	nick_flag_manu = 0;
	int chann_flag_manu = 0;
	if (cmd.size() < 3)
	{
		std::string str = ":ircserv 461 " + client->nickname + " " + cmd[0] + " :Not enough parameters\n";
		send(client->fd, str.data(), str.length(), 0);
		return ;
	}
	else
	{
		size_t i = 0;
		if (!clients.empty())
		{
			for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
			{
				if (clients.at(i)->nickname == cmd[1])
				{
					nick_flag_manu += 1;
					continue ;
				}
				i++;
			}
		}
		i = 0;
		if (!channels.empty())
		{
			for (std::vector<Channel *>::iterator it = channels.begin(); it != channels.end(); ++it)
			{
				if (channels.at(i)->getName() == cmd[2])
				{
					chann_flag_manu += 1;
					continue ;
				}
				i++;
			}
		}
		if (!nick_flag_manu)
		{
			std::string str = ":ircserv 401 " + client->nickname + " " + cmd[1] + " :No such nick/channel\n";
			send(client->fd, str.data(), str.length(), 0);
			return ;
		}
		else if (!chann_flag_manu)
		{
			std::string str = ":ircserv 403 " + client->nickname + " " + cmd[2] + " :No such channel\n";
			send(client->fd, str.data(), str.length(), 0);
			return ;
		}
		else
		{
			for (std::vector<Channel *>::iterator it = channels.begin(); it != channels.end(); ++it)
			{
				if ((*it)->getName() == cmd[2])
				{
					for (std::vector<ft::pair<std::string, int> >::iterator ite = (*it)->clients.begin(); ite != (*it)->clients.end(); ++ite)
					{
						if (ite->first == cmd[1])
						{
							std::stringstream str;
							str << ":ircserv 443 " << cmd[2] << ' ' << cmd[1] << " :is already on channel\n";
							send(client->fd, str.str().data(), str.str().length(), 0);
							return ;
						}
					}
				}
			}
			for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
			{
				if ((*it)->nickname == cmd[1])
				{
					std::stringstream str;
					str << ":" << client->nickname << " INVITE " << cmd[1] << " :" << cmd[2] << '\n';
					send((*it)->fd, str.str().data(), str.str().length(), 0);
                    std::stringstream tmp;
                    tmp << ":NOTICE "<<  "@" << cmd[2] << " :" << client->nickname << " invited " << cmd[1] << " into the channel" << '\n';
                    send((client)->fd, tmp.str().data(), tmp.str().length(), 0);
					return ;
				}
			}
		}
	}
}
