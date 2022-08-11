#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"
#include <iostream>
#include <iomanip>

class PhoneBook
{
	int		number;
	int		overlap;
	Contact	contact[8];

	public:
		void AddingContact(Contact new_contact);
		void SearchingContacts();
		PhoneBook();
		~PhoneBook();
};

#endif
