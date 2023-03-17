#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "ircserv.hpp"

class Channel
{
	std::string	name;

	public:
		std::vector< ft::pair<std::string, int> > clients;

		Channel(std::string name) : name(name) {}
		~Channel() {}
		std::string getName() { return (name); }
		void send_userlist();
	private:
		Channel();
};

#endif
