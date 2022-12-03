#include "vector.hpp"

int main()
{
	try
	{
		ft::vector<int> test(2, 42);
		test.push_back(66);
		std::cout << "Size : " << test.size() << std::endl;
		std::cout << "Capacity : " << test.capacity() << std::endl;
		for (ft::vector<int>::iterator i = test.begin() ; i != test.end() ; ++i)
		{
			std::cout << *i << std::endl;
		}
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
