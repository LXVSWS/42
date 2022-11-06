#include "easyfind.hpp"

int main()
{
	std::vector<int> vector (10, 42);
	try
	{
		int result = easyfind(vector, 42);
		std::cout << "An occurence of " << result << " has been found inside the container" << std::endl;
	}
	catch(const int e)
	{
		std::cout << "Zero occurence of " << e << " as been found inside the container" << std::endl;
	}
	return (0);
}
