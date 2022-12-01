#include "vector.hpp"

int main()
{
	try
	{
		ft::vector<int> test;
		std::cout << test << std::endl;
		ft::vector<int> test2(10);
		std::cout << test2 << std::endl;
		test.reserve(10);
		std::cout << test << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
