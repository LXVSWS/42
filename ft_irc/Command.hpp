#pragma once

#include "ircserv.hpp"
#include "Server.hpp"

class Client;

class Command
{
	public:
		Command();
		Command(Command &other);
		Command(std::vector<std::string> cmd, Client* client, std::string buffer);
		~Command();
		Command &operator=(Command &other);
		// parsing function
		void 	parse_commands();
		int		is_command(std::string str);
		void	upper_commands();
		void	remove_backslash();
		void	regroup_last_args();
		void 	check_prefix();
		void 	parse_user();
		void 	parse_user_wtf();
		void	parse_quit();
		void 	parse_join();
		void 	parse_msg(std::string str);
		void 	parse_kick();
		void 	parse_topic();
		void 	parse_mode();
		void 	parse_kill();
		void    control(std::string buffer);
		unsigned int	coma_count(std::string str);
		std::vector<std::string> split(std::string arg);
		std::vector<std::string> get_next_command();
		std::vector<std::string> return_vector();
		std::vector<std::string> command;
		std::string prefix;
		// attributes
		bool 		is_prefix;
		bool		o_mode;
		bool		join_flag;
		Client		*cl;
	private:
};
