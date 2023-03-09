#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "ircserv.hpp"

class Client
{
	bool password_valid;
	std::string nickname;
	std::string host;
	std::string username;
	std::string server;

	public:
		int fd;
		Client(int fd) : password_valid(false), fd(fd) {}
		~Client() {}
		void toggle_password(bool success) { password_valid = success; }
		void set_nickname(std::string nick) { nickname = nick; }
	private:
		Client();
};

#endif
