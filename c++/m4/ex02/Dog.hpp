#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
	Brain *brain;

	public:
		Dog();
		Dog(const Dog& src);
		Dog& operator=(const Dog& right);
		~Dog();

		void makeSound() const;
};

#endif
