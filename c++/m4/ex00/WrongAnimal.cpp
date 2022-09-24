#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal()
{
	std::cout << "WrongAnimal constructor called" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& src)
{
	*this = src;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& right)
{
	if (this != &right)
		this->type = right.type;
	return (*this);
}

WrongAnimal::~WrongAnimal()
{
	std::cout << "WrongAnimal destructor called" << std::endl;
}

void WrongAnimal::makeSound() const
{
	std::cout << "WrongAnimal sound!" << std::endl;
}

std::string WrongAnimal::getType() const
{
	return (this->type);
}
