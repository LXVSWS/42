#include "vector.hpp"
#include "map.hpp"

int main()
{
	try
	{
		ft::map<int, std::string> test;
		test.insert(ft::pair<int, std::string>(10, "test"));
		test.insert(ft::pair<int, std::string>(0, "test"));
		test.insert(ft::pair<int, std::string>(20, "test"));
		test.insert(ft::pair<int, std::string>(15, "test"));
		test.insert(ft::pair<int, std::string>(65, "test"));
		test.insert(ft::pair<int, std::string>(60, "test"));
		test.insert(ft::pair<int, std::string>(50, "test"));
		test.insert(ft::pair<int, std::string>(35, "test"));
		test.insert(ft::pair<int, std::string>(30, "test"));
		test.insert(ft::pair<int, std::string>(40, "test"));
		test.insert(ft::pair<int, std::string>(55, "test"));
		for (ft::map<int, std::string>::iterator it = test.begin() ; it != test.end() ; ++it)
			std::cout << it->first << " => " << it->second << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
