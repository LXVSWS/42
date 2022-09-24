#include "FragTrap.hpp"

FragTrap::FragTrap()
{
	std::cout << "FragTrap default constructor called" << std::endl;
	this->hp = 100;
	this->ep = 100;
	this->ad = 30;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	std::cout << "FragTrap overloaded constructor called" << std::endl;
	this->hp = 100;
	this->ep = 100;
	this->ad = 30;
}

FragTrap::FragTrap(const FragTrap& src)
{
	*this = src;
}

FragTrap& FragTrap::operator=(const FragTrap& right)
{
	if (this != &right)
	{
		this->name = right.name;
		this->hp = right.hp;
		this->ep = right.ep;
		this->ad = right.ad;
	}
	return (*this);
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap destructor called" << std::endl;
}

void FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap " << this->name << " ask for high fives!" << std::endl;
}
