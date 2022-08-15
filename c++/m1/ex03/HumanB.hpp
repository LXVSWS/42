#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"
#include <iostream>

class HumanB
{
	public:
		Weapon		weapon;
		std::string	name;

		void attack(void);
		void setWeapon(Weapon weapon);
		HumanB(std::string name);
		~HumanB();
};

#endif
