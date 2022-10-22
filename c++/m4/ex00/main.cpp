#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
	const Animal* meta = new Animal();
	const Animal* i = new Cat();
	const Animal* j = new Dog();
	const WrongAnimal* k = new WrongAnimal();
	const WrongAnimal* wrong = new WrongCat();

	std::cout << "Animal :" << std::endl;
	meta->makeSound();
	std::cout << i->getType() << " :" << std::endl;
	i->makeSound();
	std::cout << j->getType() << " :" << std::endl;
	j->makeSound();
	std::cout << k->getType() << "WrongAnimal :" << std::endl;
	k->makeSound();
	std::cout << wrong->getType() << " :" << std::endl;
	wrong->makeSound();

	delete meta;
	delete j;
	delete i;
	delete k;
	delete wrong;

	return (0);
}
