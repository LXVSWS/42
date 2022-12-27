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
		ft::vector<int>::iterator itt = test.begin();
		ft::vector<int>::iterator itret = test.insert(itt, 88);
		for (ft::vector<int>::iterator it = test.begin() ; it != test.end() ; ++it)
			std::cout << *it << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
