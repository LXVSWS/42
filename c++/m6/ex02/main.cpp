#include "Base.hpp"

Base *generate(void) // implement random
{
	return (new C);
}

void identify(Base *p)
{
	if (dynamic_cast<A *>(p))
		std::cout << "A detected" << std::endl;
	else if (dynamic_cast<B *>(p))
		std::cout << "B detected" << std::endl;
	else if (dynamic_cast<C *>(p))
		std::cout << "C detected" << std::endl;
	else
		std::cout << "Error" << std::endl;
}

void identify(Base& p)
{
	(void)p;
	std::cout << "Fix me" << std::endl;
}

int main()
{
	Base *ptr = generate();
	std::cout << "Identify pointer: " << std::endl;
	identify(ptr);
	std::cout << "Identify reference: " << std::endl;
	return (0);
}
