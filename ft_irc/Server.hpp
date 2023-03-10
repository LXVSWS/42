#ifndef SERVER_HPP
#define SERVER_HPP

#include "ircserv.hpp"
#include "Client.hpp"

class Client;

class Server
{
	int port;
	std::string password;
	int sockfd;

	public:
		Server(int port, std::string password);
		~Server() {}
		int init();
		int loop();
		int sock() const { return (sockfd); }
		std::vector<std::string> check(char *buffer);
		int handle(std::vector<std::string> cmd, Client* client);
	private:
		Server();
};

#endif
