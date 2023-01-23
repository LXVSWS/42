#include "vector.hpp"
#include "map.hpp"
#include <map>

int main()
{
	try
	{
		ft::map<int, std::string> test;
		ft::pair<ft::map<int, std::string>::iterator, bool> pair = test.insert(ft::pair<int, std::string>(1, "test"));
		ft::map<int, std::string>::iterator itt = pair.first;
		std::cout << "\n" << itt->first << std::endl;
		test.insert(ft::pair<int, std::string>(0, "test"));
		test.insert(ft::pair<int, std::string>(6, "test"));
		test.insert(ft::pair<int, std::string>(2, "test"));
		test.insert(ft::pair<int, std::string>(5, "test"));
		test.insert(ft::pair<int, std::string>(3, "test"));
		test.insert(ft::pair<int, std::string>(4, "test"));

		for (ft::map<int, std::string>::iterator it = test.begin() ; it != test.end() ; ++it)
			std::cout << it->first << std::endl;
		std::cout << test.end()->first << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
