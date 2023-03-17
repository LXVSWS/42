#include "Client.hpp"

void Client::authentification()
{
	if (password_valid == true && nickname.size() && username.size() \
	&& hostname.size() && servername.size() && realname.size())
	{
		auth = true;
		std::stringstream ss;
		ss << ":ircserv NOTICE * :*** You are now registered! Welcome " << nickname << " !\n";
		send(fd, ss.str().data(), ss.str().length(), 0);
	}
}
