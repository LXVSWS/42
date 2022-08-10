#include "Contact.hpp"
#include <iostream>

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
