#include "iter.hpp"

int main()
{
	int *tab = new int[10];
	for (int i = 0 ; i < 10 ; i++)
		tab[i] = i;
	std::cout << "Using function template on int:" << std::endl;
	iter(tab, 10, fct);

	char *tab2 = new char[10];
	for (int i = 0 ; i < 10 ; i++)
		tab2[i] = 97 + i;
	std::cout << "Using function template on char:" << std::endl;
	iter(tab2, 10, fct);

	delete[] tab;
	delete[] tab2;

	return (0);
}
