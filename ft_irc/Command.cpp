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

Command::Command(std::vector<std::string> cmd, Client* client, std::string buffer) : command(cmd), is_prefix(false) {
	cl = client;
	(void) buffer;
	control(buffer);
	remove_backslash();
	parse_commands();

	// for (std::vector<std::string>::iterator it = command.begin() ; it != command.end() ; ++it) {
	// 		std::cout << "Command CLASS -> " << *it << std::endl;
	// }
}

Command::~Command() {}

int	Command::is_command(std::string str)
{
	for (int i = 0; i < 10; i++) {
		if (command[i] == str)
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

void	Command::parse_commands()
{
	if (command.empty())
		return ;
	check_prefix();
	if (command[0] == "USER")
		parse_user();
	else if (command[0] == "CAP")
		parse_user_wtf();
	if (command[0] == "QUIT")
		parse_quit();
	if (command[0] == "JOIN")
		parse_join();
	if (command[0] == "PRIVMSG")
		parse_msg();
	if (command[0] == "KICK")
		parse_kick();
	if (command[0] == "TOPIC")
		parse_topic();
}

void Command::parse_user(void)
{
	if (command.size() > 4 && command[4].at(0) == ':')
		regroup_last_args();
}

void Command::parse_user_wtf(void)
{
		regroup_last_args();
}

void Command::parse_quit(void)
{
	if (command.size() > 1 && command[1].at(0) == ':')
		regroup_last_args();
}

void Command::parse_join(void)
{
	unsigned int i = 0;
	std::stringstream forgeron;
	std::vector<std::string>::iterator it = command.begin();
	it++;
	while (i < (*it).size())
	{
		if ((*it).at(i) != ',')
			forgeron << (*it)[i];
		else
			break;
		i++;
	}
	command[1] = forgeron.str();
}

void Command::parse_msg(void)
{
	if (command.size() > 2 && command[2].at(0) == ':')
		regroup_last_args();
}

void Command::parse_kick(void)
{
	if (command.size() > 3 && command[3].at(0) == ':')
		regroup_last_args();
}

void Command::parse_topic(void)
{
	if (command.size() > 2 && command[2].at(0) == ':')
		regroup_last_args();
}

void	Command::remove_backslash(void)
{
	for (std::vector<std::string>::iterator it = command.begin() ; it != command.end() ; ++it)
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

void	Command::control(std::string buffer)
{
	if (command.empty())
		return ;
	if (buffer.find('\r') != std::string::npos)
		if (buffer.find('\n') != std::string::npos)
			return ;
	if (command.back().find('\n') != std::string::npos)
	{
		if (cl->tmp.empty())
			return ;
		else
		{
			std::stringstream tmp;
			for (std::vector<std::string>::iterator it = cl->tmp.begin() ; it != cl->tmp.end() ; ++it)
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
			return ;
		std::stringstream slot;
		if (buffer.find(' ') != std::string::npos)
			slot << buffer;
		else
		{
			for (std::vector<std::string>::iterator it = this->command.begin() ; it != this->command.end() ; ++it)
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
		for (size_t i = 0 ; i < token.length() ; ++i)
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
	for (std::vector<std::string>::iterator it = tokens.begin() ; it != tokens.end() ; ++it)
		if (it->back() == '\n')
			it->pop_back();
	return (tokens);
}