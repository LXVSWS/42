#include "vector.hpp"

int main()
{
	try
	{
		ft::vector<int> test(1);
		test.push_back(42);
		ft::vector<int>::iterator i = test.begin();
		std::cout << &i << " : " << *i << std::endl;
		std::cout << "Size : " << test.size() << std::endl;
		std::cout << "Capacity : " << test.capacity() << std::endl;
		std::cout << "Original Capacity : " << test.original_capacityy() << std::endl;
		//ft::vector<int> test2(test);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
