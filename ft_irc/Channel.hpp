#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "ircserv.hpp"

class Channel
{
	std::string name;
	std::string topic;

	public:
		std::vector< ft::pair<std::string, int> > clients;
		std::vector<std::string> operators;

		Channel(std::string name): name(name) {}
		~Channel() {}
		std::string getName() const { return (name); }
		std::string getTopic() { return (topic); }
		void setTopic(std::string str) { topic = str; }
		void send_userlist();
	private:
		Channel();
};

#endif
