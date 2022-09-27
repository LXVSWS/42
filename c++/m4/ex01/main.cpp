#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
	Animal *tab[4];
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	for (int i = 0 ; i < 4 ; i++)
	{
		if (i < 2)
			tab[i] = new Cat();
		else
			tab[i] = new Dog();
	}
	for (int i = 0 ; i < 4 ; i++)
		delete tab[i];

	delete j;
	delete i;

	return (0);
}
