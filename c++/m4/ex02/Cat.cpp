#include "Cat.hpp"

Cat::Cat()
{
	std::cout << "Cat constructor called" << std::endl;
	this->type = "Cat";
	this->brain = new Brain();
}

Cat::Cat(const Cat& src)
{
	std::cout << "Cat copy constructor called" << std::endl;
	this->type = src.type;
	this->brain = new Brain();
	*(this->brain) = *(src.brain);
}

Cat& Cat::operator=(const Cat& right)
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

Cat::~Cat()
{
	std::cout << "Cat destructor called" << std::endl;
	delete this->brain;
}

void Cat::makeSound() const
{
	std::cout << "Meow!" << std::endl;
}
