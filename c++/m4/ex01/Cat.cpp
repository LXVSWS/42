#include "Cat.hpp"

Cat::Cat()
{
	std::cout << "Cat constructor called" << std::endl;
	this->type = "Cat";
	this->brain = new Brain();
}

Cat::Cat(const Cat& src)
{
	*this = src;
}

Cat& Cat::operator=(const Cat& right)
{
	if (this != &right)
	{
		this->type = right.type;
		this->brain = right.brain;
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
