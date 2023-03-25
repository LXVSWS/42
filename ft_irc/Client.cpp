#include "Client.hpp"

void Client::authentification()
{
	if (password_valid == true && nickname.size() && username.size() && hostname.size() && servername.size() && realname.size())
	{
		auth = true;
		std::stringstream s;
		s << ":ircserv NOTICE " << nickname << " :You are now registered! Welcome " << nickname << " !\n";
		send(fd, s.str().data(), s.str().length(), 0);
		std::stringstream s1;
		s1 << ":ircserv 375 " << nickname << " :- ircserv Message of the Day -\n";
		send(fd, s1.str().data(), s1.str().length(), 0);
		std::stringstream s2;
		s2 << ":ircserv 372 " << nickname << " :- ft_irc\n";
		send(fd, s2.str().data(), s2.str().length(), 0);
		std::stringstream s0;
		s0 << ":ircserv 372 " << nickname << " :- 42 project\n";
		send(fd, s0.str().data(), s0.str().length(), 0);
		std::stringstream s3;
		s3 << ":ircserv 376 " << nickname << " :End of /MOTD command.\n";
		send(fd, s3.str().data(), s3.str().length(), 0);
	}
}
