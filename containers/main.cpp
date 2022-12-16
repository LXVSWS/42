#include "vector.hpp"
#include "iterator.hpp"
#include "map.hpp"
#include "utils.hpp"

int main()
{
	try
	{
		ft::vector<int> test(2, 42);
		test.push_back(666);
		for (ft::vector<int>::iterator it = test.begin() ; it != test.end() ; ++it)
			std::cout << *it << std::endl;
		std::cout << "-----------------------------------" << std::endl;
		for (ft::vector<int>::reverse_iterator itt = test.rbegin() ; itt != test.rend() ; ++itt)
			std::cout << *itt << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
