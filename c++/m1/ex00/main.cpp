#include "Zombie.hpp"

int main()
{
	Zombie *zombie = newZombie("John");
	randomChump("Jack");
	zombie->announce();
	delete zombie;
	return (0);
}
