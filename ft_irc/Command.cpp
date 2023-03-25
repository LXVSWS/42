#include "Command.hpp"

Command::Command() {};

Command::Command(Command &other)
{
	if (this != &other)
		*this = other;
}

Command& Command::operator=(Command &other)
{
	if (this != &other)
		*this = other;
	return (*this);
}

Command::Command(std::vector<std::string> cmd, Client* client, std::string buffer) : command(cmd), is_prefix(false), o_mode(false) {
	cl = client;
	control(buffer);
	remove_backslash();
	parse_commands();
}

Command::~Command() {}

int	Command::is_command(std::string str)
{
	std::string check[24] = {"USER", "user", "NICK", "nick", "PASS", "pass", "QUIT", "quit", "JOIN", "join", "PRIVMSG", "privmsg", "NOTICE", "notice", "MODE", "mode", "TOPIC", "topic", "KILL", "kill", "INVITE", "invite", "KICK", "kick"};
	for (int i = 0; i < 24; i++) {
		if (check[i] == str)
			return 1;
	}
	return (0);
}

void Command::check_prefix()
{
	std::vector<std::string>::iterator it = command.begin();
	if ((*it)[0] == ':' && (*it)[1])
	{
		prefix = (*it);
		is_prefix = true;
		command.erase(command.begin());
	}
}

void	Command::regroup_last_args()
{
	std::vector<std::string>::iterator it = command.begin();
	while (it != command.end())
	{
		if ((*it)[0] == ':')
		{
			std::vector<std::string>::iterator replace = it;
			std::stringstream ss;
			while (it != command.end())
			{
				ss << (*it);
				ss << ' ';
				it++;
			}
			command.erase(replace, command.end());
			command.push_back(ss.str());
			break;
		}
		it++;
	}
}

std::vector<std::string> Command::get_next_command() {
	std::vector<std::string> next_cmd;

	std::vector<std::string>::iterator it = command.begin();
	if (is_command(*it))
	{
		next_cmd.push_back((*it));
		command.erase(command.begin());
	}
	std::vector<std::string>::iterator iter = command.begin();
	while (iter != command.end() && !is_command(*iter))
	{
		next_cmd.push_back((*iter));
		command.erase(iter);
		it++;
	}
	return (next_cmd);
}

void	Command::upper_commands()
{
	for (unsigned int i = 0; i < (command[0]).size(); i++)
		(command[0]).at(i) = std::toupper((command[0]).at(i));
}

void	Command::parse_commands()
{
	if (command.empty())
		return ;
	check_prefix();
	upper_commands();
	if (command[0] == "USER")
		parse_user();
	else if (command[0] == "CAP")
		parse_user_wtf();
	if (command[0] == "QUIT")
		parse_quit();
	if (command[0] == "JOIN")
		parse_join();
	if (command[0] == "NOTICE")
		parse_msg("NOTICE");
	if (command[0] == "PRIVMSG")
		parse_msg("PRIVMSG");
	if (command[0] == "KICK")
		parse_kick();
	if (command[0] == "TOPIC")
		parse_topic();
	if (command[0] == "MODE")
		parse_mode();
	if (command[0] == "KILL")
		parse_kill();
}

void Command::parse_kill(void)
{
	if (command.size() < 3)
	{
		command.clear();
		command.push_back("KILL");
		return ;
	}
	if (command.size() > 2 && command[2].at(0) == ':')
		regroup_last_args();
}

void Command::parse_user(void)
{
	if (command.size() > 4 && command[4].at(0) == ':')
		regroup_last_args();
}

void Command::parse_quit(void) 
{
	if (command.size() < 2)
	{
		command.clear();
		command.push_back("QUIT");
		command.push_back("Bye");
		return ;
	}
	if (command.size() > 1 && command[1].at(0) == ':')
		regroup_last_args();
}

void Command::parse_user_wtf(void)
{
		regroup_last_args();
}

unsigned int Command::coma_count(std::string str)
{
	unsigned int i = 0;
	unsigned int j = 1;
	while (i < str.size())
	{
		if (str[i] == ',')
			j++;
		i++;
	}
	return (j);
}

void Command::parse_join(void)
{
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int count;
	std::stringstream forgeron;
	std::string tmp;
	if (command.size() < 2)
	{
		command.clear();
		command.push_back("JOIN");
		return;
	}
	tmp = command[1];
	command.clear();
	command.push_back("JOIN");
	count = coma_count(tmp);
	while (i < count)
	{
		forgeron.str(std::string());
		while (j < tmp.size() && tmp[j] && tmp[j] != ',')
		{
			forgeron << tmp[j];
			j++;
		}
		while (tmp[j] == ',')
			j++;
		if (forgeron.str().size())
			command.push_back(forgeron.str());
		i++;
	}
}

void Command::parse_msg(std::string str)
{
	unsigned int count;
	unsigned int i = 0;
	unsigned int j = 0;
	std::stringstream forgeron;
	if (command.size() < 3)
	{
		command.clear();
		command.push_back(str);
		return;
	}
	if (command.size() > 2 && command[2].at(0) == ':')
		regroup_last_args();
	std::string save = command[2];
	std::string tmp = command[1];
	if (tmp.empty() || save.empty())
		return;
	command.clear();
	command.push_back(str);
	count = coma_count(tmp);
	while (i < count)
	{
		forgeron.str(std::string());
		while (j < tmp.size() && tmp[j] && tmp[j] != ',')
		{
			forgeron << tmp[j];
			j++;
		}
		while (tmp[j] == ',')
			j++;
		if (forgeron.str().size())
			command.push_back(forgeron.str());
		i++;
	}
	command.push_back(save);
}

void Command::parse_kick(void)
{
	if (command.size() < 3)
	{
		command.clear();
		command.push_back("KICK");
		return ;
	}
	unsigned int coma_canal = 0;
	unsigned int coma_users = 0;
	unsigned int i = 0;
	unsigned int j = 0;
	std::stringstream forgeron;
	std::string save_commentary;
	std::string save_users;
	std::string save_canal;
	if (command.size() >= 4 && command[3].at(0) == ':')
		regroup_last_args();
	if (command.size() >= 4)
		save_commentary = command[3];
	if (command.size() >= 3)
		save_users = command[2];
	if (command.size() >= 2)
		save_canal = command[1];
	coma_canal = coma_count(save_canal);
	coma_users = coma_count(save_users);
	if (coma_canal > 1 || coma_users > 1)
	{
		command.clear();
		command.push_back("KICK");
	}
	if (coma_canal > 1)
	{
		while (i < coma_canal)
		{
			forgeron.str(std::string());
			while (j < save_canal.size() && save_canal[j] && save_canal[j] != ',')
			{
				forgeron << save_canal[j];
				j++;
			}
			while (save_canal[j] == ',')
				j++;
			if (forgeron.str().size())
				command.push_back(forgeron.str());
			i++;
		}
		if (coma_users == 1)
		{
			command.push_back(",");
			command.push_back(save_users);
			if (save_commentary.size())
				command.push_back(save_commentary);
			return;
		}
	}
	if (coma_canal == 1 && coma_users == 1)
	{
		command.clear();
		command.push_back("KICK");
		command.push_back(save_canal);
		command.push_back(",");
		command.push_back(save_users);
	}
	i = 0;
	j = 0;
	if (coma_users > 1)
	{
		if (coma_canal == 1)
			command.push_back(save_canal);
		command.push_back(",");
		while (i < coma_users)
		{
			forgeron.str(std::string());
			while (j < save_users.size() && save_users[j] && save_users[j] != ',')
			{
				forgeron << save_users[j];
				j++;
			}
			while (save_users[j] == ',')
				j++;
			if (forgeron.str().size())
				command.push_back(forgeron.str());
			i++;
		}
	}
	command.push_back(",");
	if (save_commentary.size())
		command.push_back(save_commentary);
}

void Command::parse_topic(void)
{
	if (command.size() > 2 && command[2].at(0) == ':')
		regroup_last_args();
}

void Command::parse_mode(void)
{
	if (command.size() < 4)
		return;
	if (command[2].at(0) == '-')
		o_mode = false;
	if (command[2].at(0) == '+')
		o_mode = true;
}

void Command::remove_backslash(void)
{
	for (std::vector<std::string>::iterator it = command.begin(); it != command.end(); ++it)
		if (it->back() == '\n')
			it->pop_back();
	if (command.size() == 1)
		if (command.at(0).empty())
			command.clear();
}

std::vector<std::string> Command::return_vector(void)
{
	return command;
}

void Command::control(std::string buffer)
{
	if (command.empty())
		return;
	if (buffer.find('\r') != std::string::npos)
		if (buffer.find('\n') != std::string::npos)
			return;
	if (command.back().find('\n') != std::string::npos)
	{
		if (cl->tmp.empty())
			return;
		else
		{
			std::stringstream tmp;
			for (std::vector<std::string>::iterator it = cl->tmp.begin(); it != cl->tmp.end(); ++it)
				tmp << *it;
			if (buffer.find(' ') != std::string::npos)
				tmp << buffer;
			else
				for (std::vector<std::string>::iterator it = command.begin(); it != command.end(); it++)
					tmp << *it;
			command.clear();
			command = split(tmp.str());
			cl->tmp.clear();
		}
	}
	else
	{
		if (command.empty())
			return;
		std::stringstream slot;
		if (buffer.find(' ') != std::string::npos)
			slot << buffer;
		else
		{
			for (std::vector<std::string>::iterator it = this->command.begin(); it != this->command.end(); ++it)
				slot << *it;
		}
		cl->tmp.push_back(slot.str());
		command.clear();
	}
}

std::vector<std::string> Command::split(std::string buffer)
{
	std::vector<std::string> tokens;
	std::stringstream ss(buffer);
	std::string token;
	char toggle = 0;
	while (std::getline(ss, token, ' '))
	{
		if (!token.size() || token == "\r\n")
			continue;
		for (size_t i = 0; i < token.length(); ++i)
			if (token.at(i) == '\r' && token.at(i + 1) == '\n')
			{
				tokens.push_back(token.substr(0, i));
				std::string str = token.substr(i + 2);
				if (!str.empty() && str.front() != '\n')
					tokens.push_back(str);
				toggle = 1;
				break;
			}
		if (!toggle)
			tokens.push_back(token);
		else
			toggle = 0;
	}
	for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it)
		if (it->back() == '\n')
			it->pop_back();
	return (tokens);
}
