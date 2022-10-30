#include "Base.hpp"

Base *generate(void)
{
	std::default_random_engine random(std::chrono::steady_clock::now().time_since_epoch().count());
	if (random() % 3 == 0)
		return (new A);
	else if (random() % 3 == 1)
		return (new B);
	else
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
}

void identify(Base& p)
{
	try
	{
		if (&dynamic_cast<A &>(p))
			std::cout << "A detected" << std::endl;
	}
	catch(const std::exception& e)
	{
		try
		{
			if (&dynamic_cast<B &>(p))
				std::cout << "B detected" << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cout << "C detected" << std::endl;
		}
	}
}

int main()
{
	Base *ptr = generate();
	std::cout << "Identify pointer: " << std::endl;
	identify(ptr);
	std::cout << "Identify reference: " << std::endl;
	identify(*ptr);
	delete ptr;
	return (0);
}
