#include "Zombie.hpp"

int main()
{
	Zombie *zombie = newZombie("John"); // allocate on the heap when the size of the data is known at runtime
	zombie->announce();
	delete zombie;
	randomChump("Jack"); // allocate on the stack when the size of the data is known at compilation time
	return (0);
}
