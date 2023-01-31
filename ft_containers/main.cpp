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
		test.insert(test.begin(), ft::pair<int, std::string>(25, "test"));

		for (ft::map<int, std::string>::iterator it = test.begin() ; it != test.end() ; ++it)
			std::cout << it.base() << " : " << it->first << " => " << it->second << std::endl;

		ft::vector<int> test2;
		test2.push_back(1);
		test2.push_back(42);
		test2.push_back(88888);
		test2.push_back(44);
		test2.push_back(666);

		for (ft::vector<int>::iterator it = test2.begin() ; it != test2.end() ; ++it)
			std::cout << it.base() << " : " << *it << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
