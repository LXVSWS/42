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
		test.insert(ft::pair<int, std::string>(30, "test"));
		test.insert(ft::pair<int, std::string>(40, "test"));
		ft::map<int, std::string> test2;
		test2.insert(ft::pair<int, std::string>(999, "test"));
		test2.insert(ft::pair<int, std::string>(9999, "test"));
		test2.insert(ft::pair<int, std::string>(99, "test"));
		for (ft::map<int, std::string>::iterator it = test.begin() ; it != test.end() ; ++it)
			std::cout << &it << " : " << it->first << " => " << it->second << std::endl;
		std::cout << "size : " << test.size() << std::endl;
		test2 = test;
		for (ft::map<int, std::string>::iterator it = test2.begin() ; it != test2.end() ; ++it)
			std::cout << &it << " : " << it->first << " => " << it->second << std::endl;
		std::cout << "size : " << test2.size() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
