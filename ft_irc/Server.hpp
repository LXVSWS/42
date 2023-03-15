#ifndef SERVER_HPP
#define SERVER_HPP

#include "ircserv.hpp"
#include "Client.hpp"
#include "Channel.hpp"

class Client;

class Server
{
	int port;
	int sockfd;
	std::string password;

	public:
		Server(int port, std::string password);
		~Server() {}
		int init();
		void loop();
		int sock() const { return (sockfd); }
		std::vector<std::string> check(char *buffer);
		int handle(std::vector<std::string>	cmd, std::vector<Client*> clients, Client* client);
	private:
		Server();
};

#endif
