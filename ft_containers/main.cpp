#include "vector.hpp"
#include "map.hpp"

int main()
{
	try
	{
		ft::map<int, std::string> test;
		test.insert(ft::pair<int, std::string>(1, "test"));
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
