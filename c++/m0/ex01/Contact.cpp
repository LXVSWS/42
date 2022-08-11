#include "Contact.hpp"

std::string Contact::getFirstName()
{
	return (this->first_name);
}

std::string Contact::getLastName()
{
	return (this->last_name);
}

std::string Contact::getNickname()
{
	return (this->nickname);
}

std::string Contact::getPhoneNumber()
{
	return (this->phone_number);
}

std::string Contact::getDarkestSecret()
{
	return (this->darkest_secret);
}

Contact::Contact(std::string fn, std::string ln, std::string n, std::string pn, std::string ds) : \
first_name(fn), last_name(ln), nickname(n), phone_number(pn), darkest_secret(ds)
{
	std::cout << "----------------------------\n" << "Contact created !" << std::endl;
}

Contact::Contact()
{
	return ;
}

Contact::~Contact()
{
	return ;
}
