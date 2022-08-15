#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <iostream>

class Weapon
{
	std::string type;

	public:
		std::string const &getType();
		void setType(std::string newtype);
		Weapon(std::string val);
		Weapon();
		~Weapon();
};

#endif
