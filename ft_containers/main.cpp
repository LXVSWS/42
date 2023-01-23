#include "vector.hpp"
#include "map.hpp"
#include <map>

int main()
{
	try
	{
		ft::map<int, std::string> test;
		test.insert(ft::pair<int, std::string>(1, "test"));
		test.insert(ft::pair<int, std::string>(0, "test"));
		test.insert(ft::pair<int, std::string>(2, "test"));
		test.insert(ft::pair<int, std::string>(6, "test"));
		test.insert(ft::pair<int, std::string>(5, "test"));
		test.insert(ft::pair<int, std::string>(3, "test"));
		test.insert(ft::pair<int, std::string>(4, "test"));
		ft::map<int, std::string>::iterator it = test.begin();
		std::cout << it->first << std::endl;
		++it;
		std::cout << it->first << std::endl;
		++it;
		std::cout << it->first << std::endl;
		++it;
		std::cout << it->first << std::endl;
		++it;
		std::cout << it->first << std::endl;
		++it;
		std::cout << it->first << std::endl;
		++it;
		std::cout << it->first << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
