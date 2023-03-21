#ifndef SERVER_HPP
#define SERVER_HPP

#include "ircserv.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Command.hpp"

class Client;
class Command;

class Server
{
	int port;
	int sockfd;
	const std::string password;

	public:
		Server(int port, std::string password);
		~Server();
		int init();
		void loop();
		int sock() const { return (sockfd); }
		void message(Client* client, fd_set& fdset, std::vector<Client*>& clients, std::vector<Channel*>& channels);
		std::vector<std::string> check(char *buffer);
		void quit(Client* client, fd_set& fdset, std::vector<Client*>& clients, std::vector<Channel*>& channels);
		int handle(std::vector<std::string>	cmd, std::vector<Client*> clients, Client* client);
		void join(std::vector<std::string>& cmd, Client* client, std::vector<Channel*>& channels);
		void privmsg(std::vector<std::string>& cmd, Client* client, std::vector<Client*>& clients, std::vector<Channel*>& channels);
		void nick(std::vector<std::string>& cmd, Client* client, std::vector<Client*>& clients, std::vector<Channel*>& channels);
		int	mode(Command *command, std::vector<Client*> clients, std::vector<Channel*> channels, Client *client);
		void kill(std::vector<std::string>& cmd, Client* client, fd_set& fdset, std::vector<Client*>& clients, std::vector<Channel*>& channels);
	private:
		Server();
};

#endif
