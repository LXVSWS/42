#include "PhoneBook.hpp"
#include "Contact.hpp"
#include <iostream>

void PhoneBook::GetContactsNumber()
{
	std::cout << this->number << " contact(s) stored" << std::endl;
}

void PhoneBook::AddingContact(Contact new_contact)
{
	if (this->number <= 7)
		this->contact[this->number] = new_contact;
	else
	{
		this->number = 0;
		this->contact[this->number] = new_contact;
	}
	this->number++;
	std::cout << "Contact added to phonebook" << std::endl;
	this->GetContactsNumber();
}

Contact::Contact(std::string fn, std::string ln, std::string n, std::string pn, std::string ds) : \
first_name(fn), last_name(ln), nickname(n), phone_number(pn), darkest_secret(ds)
{
	std::cout << this->first_name << " " << this->last_name << " contact created" << std::endl;
}

Contact adding()
{
	std::string s1;
	std::string s2;
	std::string s3;
	std::string s4;
	std::string s5;

	std::cout << "Adding a new contact..." << std::endl;
	std::cout << "First name : ";
	std::cin >> s1;
	std::cout << "Last name : ";
	std::cin >> s2;
	std::cout << "Nickname : ";
	std::cin >> s3;
	std::cout << "Phone number : ";
	std::cin >> s4;
	std::cout << "Darkest secret : ";
	std::cin >> s5;
	Contact contact(s1, s2, s3, s4, s5);
	return (contact);
}

int	main()
{
	PhoneBook phonebook;
	char cmd[1024];

	while (1)
	{
		std::cout << "----------------------------" << std::endl << "| Crappy Awesome Phonebook |" << \
		std::endl << "----------------------------" << std::endl << "Enter command : ";
		std::cin >> cmd;
		if (cmd[0] == 'A' && cmd[1] == 'D' && cmd[2] == 'D' && !cmd[3])
			phonebook.AddingContact(adding());
		else if (cmd[0] == 'S' && cmd[1] == 'E' && cmd[2] == 'A' && cmd[3] == 'R' && cmd[4] == 'C' && cmd[5] == 'H' && !cmd[6])
			phonebook.GetContactsNumber();
		else if (cmd[0] == 'E' && cmd[1] == 'X' && cmd[2] == 'I' && cmd[3] == 'T' && !cmd[4])
			break;
	}
	std::cout << "Good bye" << std::endl;
	return (0);
}

PhoneBook::PhoneBook()
{
	this->number = 0;
}

PhoneBook::~PhoneBook()
{
	return ;
}

Contact::Contact()
{
	return ;
}

Contact::~Contact()
{
	return ;
}
