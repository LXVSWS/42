#include "Client.hpp"

Client::Client() {}

Client::~Client() {}

void Client::toggle_password(bool success)
{
	password_valid = success;
}

void Client::set_nickname(std::string nick)
{
	nickname = nick;
}
