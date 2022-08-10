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
		if (this->contact[i].first_name.size() > 10)
		{
			resized = this->contact[i].first_name;
			resized.resize(10);
			resized[9] = '.';
			std::cout << std::setiosflags(std::ios::right) << std::setfill(' ') << std::setw(10) << resized;
		}
		else
			std::cout << std::setiosflags(std::ios::right) << std::setfill(' ') << std::setw(10) << this->contact[i].first_name;
		std::cout << " | ";
		if (this->contact[i].last_name.size() > 10)
		{
			resized = this->contact[i].last_name;
			resized.resize(10);
			resized[9] = '.';
			std::cout << std::setiosflags(std::ios::right) << std::setfill(' ') << std::setw(10) << resized;
		}
		else
			std::cout << std::setiosflags(std::ios::right) << std::setfill(' ') << std::setw(10) << this->contact[i].last_name;
		std::cout << " | ";
		if (this->contact[i].nickname.size() > 10)
		{
			resized = this->contact[i].nickname;
			resized.resize(10);
			resized[9] = '.';
			std::cout << std::setiosflags(std::ios::right) << std::setfill(' ') << std::setw(10) << resized << std::endl;
		}
		else
			std::cout << std::setiosflags(std::ios::right) << std::setfill(' ') << std::setw(10) << this->contact[i].nickname << std::endl;
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
		std::cout << "----------------------------\nFirst name : " << this->contact[i].first_name << "\nLast name : " << \
		this->contact[i].last_name << "\nNickname : " << this->contact[i].nickname << "\nPhone number : " << \
		this->contact[i].phone_number << "\nDarkest secret : " << this->contact[i].darkest_secret << std::endl;
	else
		std::cout << "Index out or range" << std::endl;
}

PhoneBook::~PhoneBook()
{
	return ;
}
