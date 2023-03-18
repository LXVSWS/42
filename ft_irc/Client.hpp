#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "ircserv.hpp"

class Client
{
	bool password_valid;
	bool auth;
	std::string username;
	std::string hostname;
	std::string servername;
	std::string realname;

	public:
		int fd;
		std::string nickname;
		std::vector<std::string> op;
		std::vector<std::string> tmp;

		Client(int fd) : password_valid(false), auth(false), fd(fd) {}
		~Client() {}
		void toggle_password(const bool success) { password_valid = success; }
		void set_nickname(const std::string& nick) { nickname = nick; }
		void set_username(const std::string& user) { username = user; }
		void set_hostname(const std::string& host) { hostname = host; }
		void set_servername(const std::string& server) { servername = server; }
		void set_realname(const std::string& name) { realname = name; }
		void authentification();
		char is_auth() const { return (auth); }
	private:
		Client();
};

#endif
