#include "Animal.hpp"

Animal::Animal()
{
	std::cout << "Animal constructor called" << std::endl;
}

Animal::Animal(const Animal& src)
{
	*this = src;
}

Animal& Animal::operator=(const Animal& right)
{
	if (this != &right)
		this->type = right.type;
	return (*this);
}

Animal::~Animal()
{
	std::cout << "Animal destructor called" << std::endl;
}

void Animal::makeSound() const
{
	if (this->type == "Cat")
		std::cout << "Meow!" << std::endl;
	else if (this->type == "Dog")
		std::cout << "Woof!" << std::endl;
}

std::string Animal::getType() const
{
	return (this->type);
}