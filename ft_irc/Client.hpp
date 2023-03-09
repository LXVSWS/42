#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "ircserv.hpp"

class Client
{
	bool password_valid;
	std::string nickname;
	std::string username;
	std::string hostname;
	std::string servername;
	std::string realname;

	public:
		int fd;
		Client(int fd) : password_valid(false), fd(fd) {}
		~Client() {}
		void toggle_password(bool success) { password_valid = success; }
		void set_nickname(std::string nick) { nickname = nick; }
		void set_username(std::string user) { username = user; }
		void set_hostname(std::string host) { hostname = host; }
		void set_servername(std::string server) { servername = server; }
		void set_realname(std::string name) { realname = name; }
	private:
		Client();
};

#endif
