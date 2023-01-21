#include "vector.hpp"
#include "map.hpp"

int main()
{
	try
	{
		ft::map<int, std::string> test;
		test.insert(ft::pair<int, std::string>(1, "test"));
		test.insert(ft::pair<int, std::string>(0, "test0"));
		test.insert(ft::pair<int, std::string>(2, "test2"));
		ft::map<int, std::string>::iterator it = test.begin();
		std::cout << it->first << " => " << it->second << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
