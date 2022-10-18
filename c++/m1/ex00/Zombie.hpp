#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>

class Zombie
{
	std::string name;

	public:
		void announce(void);
		Zombie();
		Zombie(std::string name);
		~Zombie();
};

Zombie *newZombie(std::string name);
void randomChump(std::string name);

#endif
