#include "Zombie.hpp"

int main()
{
	Zombie *zombie = newZombie("John");
	zombie->announce();
	delete zombie;
	randomChump("Jack");
	return (0);
}
