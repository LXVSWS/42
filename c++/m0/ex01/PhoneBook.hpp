#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook
{
	int		number;
	Contact	contact[8];

	public:
		void AddingContact(Contact new_contact);
		void GetContactsNumber();
		PhoneBook();
		~PhoneBook();
};

#endif
