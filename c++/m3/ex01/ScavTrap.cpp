#include "ScavTrap.hpp"

ScavTrap::ScavTrap()
{
	std::cout << "ScavTrap default constructor called" << std::endl;
	this->hp = 100;
	this->ep = 50;
	this->ad = 20;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	std::cout << "ScavTrap overloaded constructor called" << std::endl;
	this->hp = 100;
	this->ep = 50;
	this->ad = 20;
}

ScavTrap::ScavTrap(const ScavTrap& src)
{
	*this = src;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& right)
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

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap destructor called" << std::endl;
}

void ScavTrap::attack(const std::string& target)
{
	if (this->ep > 0)
	{
		std::cout << "ScavTrap " << this->name << " attacks " << target << " causing " << this->ad << " points of damage!" << std::endl;
		this->ep--;
	}
	else
		std::cout << "ScavTrap has not enough EP to attack" << std::endl;
}

void ScavTrap::guardGate()
{
	std::cout << "ScavTrap " << this->name << " cast Gate keeper mode" << std::endl;
}
