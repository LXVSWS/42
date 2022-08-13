#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>

class Zombie
{
	std::string name;

	public:
		void announce(void);
		void naming(std::string name);
		Zombie();
		~Zombie();
};

Zombie *zombieHorde(int N, std::string name);

#endif
