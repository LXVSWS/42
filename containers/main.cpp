#include "vector.hpp"

int main()
{
	try
	{
		ft::vector<int> test(3, 42);
		ft::vector<int>::iterator i = test.begin();
		std::cout << &i << " : " << *i << std::endl;
		test.push_back(42);
		std::cout << "Size : " << test.size() << std::endl;
		std::cout << "Capacity : " << test.capacity() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
