#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : name("Unknown"), hp(10), ep(10), ad(0)
{
	std::cout << "Default constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string param) : name(param), hp(10), ep(10), ad(0)
{
	std::cout << "Overloaded constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& src)
{
	*this = src;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& right)
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

ClapTrap::~ClapTrap()
{
	std::cout << "Destructor called" << std::endl;
}

void ClapTrap::attack(const std::string& target)
{
	if (this->ep > 0)
	{
		std::cout << "ClapTrap " << this->name << " attacks " << target << " causing " << this->ad << " points of damage!" << std::endl;
		this->ep--;
	}
	else
		std::cout << "Not enough EP to attack" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	std::cout << "ClapTrap " << this->name << " got hit! " << amount << " damage taken" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (this->ep > 0)
	{
		std::cout << "ClapTrap " << this->name << " repair! +" << amount << " hp" << std::endl;
		this->ep--;
	}
	else
		std::cout << "Not enough EP to repair" << std::endl;
}
