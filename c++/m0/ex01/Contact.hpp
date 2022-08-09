#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>

class Contact
{
	std::string first_name;
	std::string last_name;
	std::string nickname;
	std::string phone_number;
	std::string darkest_secret;

	public:
		Contact(std::string fn, std::string ln, std::string n, std::string pn, std::string ds);
		Contact();
		~Contact();
};

#endif
