#include "vector.hpp"
#include "map.hpp"
#include "utils.hpp"

int main()
{
	try
	{
		ft::vector<int> test(2, 42);
		std::cout << "Size : " << test.size() << std::endl;
		std::cout << "Capacity : " << test.capacity() << std::endl;
		for (ft::vector<int>::iterator i = test.begin() ; i != test.end() ; ++i)
			std::cout << *i<< std::endl;
		ft::vector<int>::const_iterator j = static_cast<ft::vector<int>::const_iterator>(test.begin());
		test.push_back(66);
		++j;
		j++;
		std::cout << *j << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
