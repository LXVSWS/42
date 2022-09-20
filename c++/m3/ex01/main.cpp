#include "ClapTrap.hpp"

int main()
{
	ClapTrap ct("david");
	for (int i = 0 ; i < 6 ; i++)
	{
		ct.attack("goliath");
		ct.beRepaired(2);
	}
	ct.takeDamage(42);
	return (0);
}
