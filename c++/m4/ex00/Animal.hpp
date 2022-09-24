#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>

class Animal
{
	protected:
		std::string type;
	public:
		Animal();
		Animal(const Animal& src);
		Animal& operator=(const Animal& right);
		~Animal();

		void makeSound() const;
		std::string getType() const;
};

#endif
