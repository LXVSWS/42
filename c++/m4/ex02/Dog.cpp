#include "Dog.hpp"

Dog::Dog()
{
	std::cout << "Dog constructor called" << std::endl;
	this->type = "Dog";
	this->brain = new Brain();
}

Dog::Dog(const Dog& src)
{
	*this = src;
}

Dog& Dog::operator=(const Dog& right)
{
	if (this != &right)
	{
		this->type = right.type;
		this->brain = right.brain;
	}
	return (*this);
}

Dog::~Dog()
{
	std::cout << "Dog destructor called" << std::endl;
	delete this->brain;
}

void Dog::makeSound() const
{
	std::cout << "Woof!" << std::endl;
}
