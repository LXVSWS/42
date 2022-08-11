#include "PhoneBook.hpp"
#include "Contact.hpp"

static Contact adding()
{
	std::string s1, s2, s3, s4, s5;

	std::cout << "----------------------------\n" << "Adding a new contact...\n----------------------------\nFirst name : ";
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
	PhoneBook	phonebook;
	char		cmd[1024];

	while (1)
	{
		std::cout << "----------------------------\n" << "| Crappy Awesome Phonebook |\n" << \
		"----------------------------\n" << "Enter command : " << std::endl;
		std::cin >> cmd;
		if (cmd[0] == 'A' && cmd[1] == 'D' && cmd[2] == 'D' && !cmd[3])
			phonebook.AddingContact(adding());
		else if (cmd[0] == 'S' && cmd[1] == 'E' && cmd[2] == 'A' && cmd[3] == 'R' && cmd[4] == 'C' && cmd[5] == 'H' && !cmd[6])
			phonebook.SearchingContacts();
		else if (cmd[0] == 'E' && cmd[1] == 'X' && cmd[2] == 'I' && cmd[3] == 'T' && !cmd[4])
			break;
	}
	std::cout << "Good bye !" << std::endl;
	return (0);
}
