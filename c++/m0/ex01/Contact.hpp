#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>

class Contact
{
	std::string first_name, last_name, nickname, phone_number, darkest_secret;

	public:
		std::string getFirstName();
		std::string getLastName();
		std::string getNickname();
		std::string getPhoneNumber();
		std::string getDarkestSecret();
		Contact(std::string fn, std::string ln, std::string n, std::string pn, std::string ds);
		Contact();
		~Contact();
};

#endif
