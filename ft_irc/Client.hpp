#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "ircserv.hpp"
#include "Server.hpp"

class Client
{
	bool password_valid;
	std::string nickname;
	std::string host;
	std::string username;
	std::string server;

	public:
		int fd;

		Client();
		Client(int fd) : password_valid(0), fd(fd) {}
		~Client();

		void toggle_password(bool success);
		void set_nickname(std::string nick);
};

#endif
