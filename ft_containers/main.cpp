#include "vector.hpp"
#include "map.hpp"

int main()
{
	try
	{
		ft::map<int, std::string> test;
		test.insert(ft::pair<int, std::string>(0, "test"));
		test.insert(ft::pair<int, std::string>(20, "test"));
		test.insert(ft::pair<int, std::string>(-30, "test"));
		test.insert(ft::pair<int, std::string>(23, "test"));
		test.insert(ft::pair<int, std::string>(-31, "test"));
		test.insert(ft::pair<int, std::string>(-29, "test"));
		test.insert(ft::pair<int, std::string>(10, "test"));
		test.insert(ft::pair<int, std::string>(100, "test"));
		test.insert(ft::pair<int, std::string>(-1, "test"));
		for (ft::map<int, std::string>::iterator it = test.begin() ; it != test.end() ; ++it)
			std::cout << it->first << std::endl;
		std::cout << "_______________________________" << std::endl;
		std::cout << "erasing : " << test.begin()->first << std::endl;
		test.erase(test.begin());
		std::cout << "erasing : " << test.begin()->first << std::endl;
		test.erase(test.begin());
		std::cout << "erasing : " << test.begin()->first << std::endl;
		test.erase(test.begin());
		std::cout << "erasing : " << test.begin()->first << std::endl;
		test.erase(test.begin());
		std::cout << "erasing : " << test.begin()->first << std::endl;
		test.erase(test.begin());
		std::cout << "erasing : " << test.begin()->first << std::endl;
		test.erase(test.begin());
		std::cout << "erasing : " << test.begin()->first << std::endl;
		test.erase(test.begin());
		std::cout << "erasing : " << test.begin()->first << std::endl;
		test.erase(test.begin());
		std::cout << "erasing : " << test.begin()->first << std::endl;
		test.erase(test.begin());
		for (ft::map<int, std::string>::iterator it = test.begin() ; it != test.end() ; ++it)
			std::cout << it->first << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
