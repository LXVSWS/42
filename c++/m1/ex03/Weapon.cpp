#include "Weapon.hpp"

std::string const &Weapon::getType()
{
	std::string const &ref = this->type;
	return (ref);
}

void Weapon::setType(std::string newtype)
{
	this->type = newtype;
}

Weapon::Weapon(std::string val) : type(val) {}

Weapon::Weapon(){}

Weapon::~Weapon(){}
