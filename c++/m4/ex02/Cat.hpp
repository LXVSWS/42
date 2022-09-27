#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal
{
	Brain *brain;

	public:
		Cat();
		Cat(const Cat& src);
		Cat& operator=(const Cat& right);
		~Cat();

		void makeSound() const;
};

#endif
