#include "Channel.hpp"

void Channel::send_userlist()
{
	for (std::vector< ft::pair<std::string, int> >::iterator it = clients.begin() ; it != clients.end() ; ++it)
	{
		std::stringstream	ss;
		std::stringstream	s;
		ss << ":ircserv 353 " << it->first << " = " << name << " :";
		for (std::vector< ft::pair<std::string, int> >::iterator it = clients.begin() ; it != clients.end() ; ++it)
			ss << it->first << ' ';
		ss << "\n";
		send(it->second, ss.str().data(), ss.str().length(), 0);
		s << ":ircserv 366 " << it->first << ' ' << name << " :End of /NAMES list.\n";
		send(it->second, s.str().data(), s.str().length(), 0);
	}
}
