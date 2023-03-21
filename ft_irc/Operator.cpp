#include "Server.hpp"

int	Server::mode(Command *command, std::vector<Client*> clients, std::vector<Channel*> channels, Client *client)
{
    if (command->command.size() < 4)
    {
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
            if ((*it)->nickname == command->command[3]) // match client and argument
            {
                for (std::vector<std::string>::iterator itt = (*it)->op.begin(); itt != (*it)->op.end(); ++itt)
                {
                    if ((*itt) == command->command[1]) // check if the client already have the operator rights
                    {
                        push = 0;
                        break;
                    }
                }
                if (push)
                {
                    (*it)->op.push_back(command->command[1]); // push the channel name into op
                    for (std::vector<Channel *>::iterator i = channels.begin(); i != channels.end(); ++i)
                    {
                        if ((*i)->getName() == command->command[1])
                        {
                            (*i)->operators.push_back(command->command[3]);
                            (*i)->send_userlist();
                        }
                        break;
                    }
                }
            }
        }
    }
    else if (command->o_mode == false && rights == 1)
    {
        for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
        {
            if ((*it)->nickname == command->command[3]) // match client and argument
            {
                for (std::vector<std::string>::iterator itt = (*it)->op.begin(); itt != (*it)->op.end(); ++itt)
                    if ((*itt) == command->command[1]) // match channel and argument
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
