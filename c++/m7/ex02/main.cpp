#include "Array.hpp"

int main()
{
	Array<int> test;
	Array<int> test2(42);
	Array<int> test3(test);
	test3 = test2;
	std::cout << test3[0] << std::endl;
	return (0);
}
