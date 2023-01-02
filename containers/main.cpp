#include "vector.hpp"
#include "map.hpp"

int main()
{
	try
	{
		ft::vector<int> test(2, 42);
		test.push_back(666);
		for (ft::vector<int>::iterator it = test.begin() ; it != test.end() ; ++it)
			std::cout << *it << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
