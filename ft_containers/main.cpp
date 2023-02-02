#include "vector.hpp"
#include "map.hpp"

int main()
{
	try
	{
		ft::map<int, std::string> test;
		test.insert(ft::pair<int, std::string>(0, "test"));
		test.insert(ft::pair<int, std::string>(22, "test"));
		test.insert(ft::pair<int, std::string>(42, "test"));
		for (ft::map<int, std::string>::iterator it = test.begin() ; it != test.end() ; ++it)
			std::cout << it.base() << " : " << it->first << " => " << it->second << std::endl;
		test.erase(test.begin());
		std::cout << "______________________________________\n" << std::endl;
		for (ft::map<int, std::string>::iterator it = test.begin() ; it != test.end() ; ++it)
			std::cout << it.base() << " : " << it->first << " => " << it->second << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
