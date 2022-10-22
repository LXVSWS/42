#include "Dog.hpp"

Dog::Dog()
{
	std::cout << "Dog constructor called" << std::endl;
	this->type = "Dog";
	this->brain = new Brain();
}

Dog::Dog(const Dog& src)
{
	std::cout << "Dog copy constructor called" << std::endl;
	this->type = src.type;
	this->brain = new Brain();
	*(this->brain) = *(src.brain);
}

Dog& Dog::operator=(const Dog& right)
{
	if (this != &right)
	{
		this->type = right.type;
		delete this->brain;
		this->brain = new Brain();
		*(this->brain) = *(right.brain);
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
