#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>

class Contact
{
	public:
		std::string first_name, last_name, nickname, phone_number, darkest_secret;
		Contact(std::string fn, std::string ln, std::string n, std::string pn, std::string ds);
		Contact();
		~Contact();
};

#endif
