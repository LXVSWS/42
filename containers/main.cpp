#include "vector.hpp"

int main()
{
	try
	{
		ft::vector<int> test;
		std::cout << test.begin() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
