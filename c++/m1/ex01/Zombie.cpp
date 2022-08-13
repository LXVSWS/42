#include "Zombie.hpp"

void Zombie::announce(void)
{
	std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::naming(std::string name)
{
	this->name = name;
}

Zombie::Zombie() {}

Zombie::~Zombie()
{
	std::cout << this->name << " died" << std::endl;
}
