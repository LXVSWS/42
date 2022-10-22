#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	delete j;
	delete i;

	Animal *tab[4];
	for (int i = 0 ; i < 4 ; i++)
	{
		if (i < 2)
			tab[i] = new Cat();
		else
			tab[i] = new Dog();
	}
	for (int i = 0 ; i < 4 ; i++)
		delete tab[i];

	Cat a;
	Cat b;
	a = b;
	Cat c;
	Cat d(c);

	Dog e;
	Dog f;
	e = f;
	Dog g;
	Dog h(g);

	return (0);
}
