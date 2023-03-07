#ifndef IRCSERV_HPP
#define IRCSERV_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/select.h>
#include <unistd.h>
#include <vector>
#include <sstream>

class Client
{
	std::string hostname;
	std::string username;
	std::string server;

	public:
		int fd;

		Client();
		Client(int fd) : fd(fd) {}
		~Client();
};

class Server
{
	int port;
	std::string password;
	int sockfd;

	public:

		Server();
		Server(int port, std::string password);
		~Server();

		int init();
		int loop();
		int sock() { return (sockfd); }
};

#endif
