#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>

class ClapTrap
{
	protected:
		std::string	name;
		int	hp;
		int	ep;
		int	ad;

	public:
		ClapTrap();
		ClapTrap(std::string);
		ClapTrap(const ClapTrap& src);
		ClapTrap& operator=(const ClapTrap& right);
		~ClapTrap();

		void attack(const std::string& target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);
};

#endif
