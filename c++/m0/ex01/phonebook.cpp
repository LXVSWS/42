#include "PhoneBook.hpp"
#include "Contact.hpp"
#include <iostream>

PhoneBook::PhoneBook()
{
	std::cout << "Phonebook started" << std::endl;
}

PhoneBook::~PhoneBook()
{
	std::cout << "Phonebook ended" << std::endl;
}

int	main()
{
	PhoneBook instance;
	char cmd[1024];

	std::cout << "Enter command : ";
	std::cin >> cmd;
	if (cmd[0] == 'A' && cmd[1] == 'D' && cmd[2] == 'D' && !cmd[3])
		std::cout << cmd << " operation called - Adding..." << std::endl;
	else if (cmd[0] == 'S' && cmd[1] == 'E' && cmd[2] == 'A' && cmd[3] == 'R' && cmd[4] == 'C' && cmd[5] == 'H' && !cmd[6])
		std::cout << cmd << " operation called - Searching..." << std::endl;
	else if (cmd[0] == 'Q' && cmd[1] == 'U' && cmd[2] == 'I' && cmd[3] == 'T' && !cmd[4])
		std::cout << cmd << " operation called - Exiting" << std::endl;
	else
		std::cout << cmd << " : invalid command" << std::endl;
	return (0);
}
