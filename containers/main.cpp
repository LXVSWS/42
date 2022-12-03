#include "vector.hpp"

int main()
{
	try
	{
		ft::vector<int> test(3, 42);
		ft::vector<int>::iterator i = test.begin();
		std::cout << &i << " : " << *i << std::endl;
		std::cout << "Size : " << test.size() << std::endl;
		std::cout << "Capacity : " << test.capacity() << std::endl;
		std::cout << "Original Capacity : " << test.original_capacityy() << std::endl;
		ft::vector<int> test2(test);
		ft::vector<int>::iterator j = test2.begin();
		test2.push_back(44);
		test2.push_back(44);
		test2.push_back(44);
		std::cout << &j << " : " << *j << std::endl;
		std::cout << "Size : " << test2.size() << std::endl;
		std::cout << "Capacity : " << test2.capacity() << std::endl;
		std::cout << "Original Capacity : " << test2.original_capacityy() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
