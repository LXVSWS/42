#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>

PhoneBook::PhoneBook()
{
	this->number = 0;
	this->overlap = 0;
}

void PhoneBook::AddingContact(Contact new_contact)
{
	if (this->number <= 7)
	{
		this->contact[this->number] = new_contact;
		this->number++;
	}
	else
	{
		if (this->overlap > 7)
			this->overlap = 0;
		this->contact[this->overlap] = new_contact;
		this->overlap++;
	}
}

void PhoneBook::SearchingContacts()
{
	int i = 0;
	std::string	resized;

	std::cout << "----------------------------\n" << this->number << " contact(s) stored" << std::endl;
	if (this->number == 0)
		return ;
	std::cout << std::endl;
	while (i < this->number)
	{
		std::cout << std::setiosflags(std::ios::right) << std::setfill(' ') << std::setw(10) << i;
		std::cout << " | ";
		if (this->contact[i].getFirstName().size() > 10)
		{
			resized = this->contact[i].getFirstName();
			resized.resize(10);
			resized[9] = '.';
			std::cout << std::setiosflags(std::ios::right) << std::setfill(' ') << std::setw(10) << resized;
		}
		else
			std::cout << std::setiosflags(std::ios::right) << std::setfill(' ') << std::setw(10) << this->contact[i].getFirstName();
		std::cout << " | ";
		if (this->contact[i].getLastName().size() > 10)
		{
			resized = this->contact[i].getLastName();
			resized.resize(10);
			resized[9] = '.';
			std::cout << std::setiosflags(std::ios::right) << std::setfill(' ') << std::setw(10) << resized;
		}
		else
			std::cout << std::setiosflags(std::ios::right) << std::setfill(' ') << std::setw(10) << this->contact[i].getLastName();
		std::cout << " | ";
		if (this->contact[i].getNickname().size() > 10)
		{
			resized = this->contact[i].getNickname();
			resized.resize(10);
			resized[9] = '.';
			std::cout << std::setiosflags(std::ios::right) << std::setfill(' ') << std::setw(10) << resized << std::endl;
		}
		else
			std::cout << std::setiosflags(std::ios::right) << std::setfill(' ') << std::setw(10) << this->contact[i].getNickname() << std::endl;
		i++;
	}
	i = 0;
	std::cout << "\nEnter contact index : " ;
	std::cin >> i;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cout << "Wrong index" << std::endl;
		return ;
	}
	else if (i >= 0 && i <= this->number - 1)
		std::cout << "----------------------------\nFirst name : " << this->contact[i].getFirstName() << "\nLast name : " << \
		this->contact[i].getLastName() << "\nNickname : " << this->contact[i].getNickname() << "\nPhone number : " << \
		this->contact[i].getPhoneNumber() << "\nDarkest secret : " << this->contact[i].getDarkestSecret() << std::endl;
	else
		std::cout << "Index out or range" << std::endl;
}

PhoneBook::~PhoneBook()
{
	return ;
}
