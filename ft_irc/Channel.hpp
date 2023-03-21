#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "ircserv.hpp"

class Channel
{
	std::string name;

	public:
		std::vector< ft::pair<std::string, int> > clients;
		std::vector<std::string> operators;

		Channel(std::string name): name(name) {}
		~Channel() {}
		std::string getName() const { return (name); }
		void send_userlist();
	private:
		Channel();
};

#endif
