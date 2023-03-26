#include "Channel.hpp"

void Channel::send_userlist()
{
	for (std::vector< ft::pair<std::string, int> >::iterator it = clients.begin() ; it != clients.end() ; ++it)
	{
		std::stringstream ss;
		std::stringstream s;
		ss << ":ircserv 353 " << it->first << " = " << name << " :";
		for (std::vector< ft::pair<std::string, int> >::iterator it = clients.begin() ; it != clients.end() ; ++it)
		{
			char toggle = 0;
			for (std::vector<std::string>::iterator itt = operators.begin() ; itt != operators.end() ; ++itt)
				if (*itt == it->first)
					toggle = 1;
			if (toggle)
				ss << '@' << it->first << ' ';
			else
				ss << it->first << ' ';
		}
		ss << "+BOT\n";
		send(it->second, ss.str().data(), ss.str().length(), 0);
		s << ":ircserv 366 " << it->first << ' ' << name << " :End of /NAMES list.\n";
		send(it->second, s.str().data(), s.str().length(), 0);
	}
}
