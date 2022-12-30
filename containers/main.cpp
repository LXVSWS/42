#include "vector.hpp"
#include "iterator.hpp"
#include "map.hpp"
#include "utils.hpp"

int main()
{
	try
	{
		ft::vector<int> test(2, 42);
		test.push_back(99);
		test.push_back(666);

		ft::vector<int> test2(2, 42);
		test2.push_back(98);
		test2.push_back(666);

		std::cout << (test == test2 ? true : false) << std::endl;
		std::cout << (test != test2 ? true : false) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
