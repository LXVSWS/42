#include "Array.hpp"

int main()
{
	Array<int> test(1);
	try
	{
		std::cout << test[0] << test[1] << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Array::InvalidIndexException" << std::endl;
	}
	return (0);
}
