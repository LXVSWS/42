#include "Base.hpp"

Base *generate(void)
{
	C *c = new C;
	return (dynamic_cast<Base *>(c));
}

void identify(Base *p)
{
	std::cout << dynamic_cast<C *>(p) << std::endl;
}

int main()
{
	identify(generate());
	return (0);
}
