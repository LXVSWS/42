#include "easyfind.hpp"

int main()
{
	std::vector<int> vector (5, 42);
	std::list<int> list (5, 41);
	std::deque<int> deque (5, 42);
	try
	{
		int result = easyfind(vector, 42);
		std::cout << "An occurence of " << result << " has been found inside the vector container" << std::endl;
	}
	catch(const int e)
	{
		std::cout << "Zero occurence of " << e << " as been found inside the vector container" << std::endl;
	}
	try
	{
		int result = easyfind(list, 42);
		std::cout << "An occurence of " << result << " has been found inside the list container" << std::endl;
	}
	catch(const int e)
	{
		std::cout << "Zero occurence of " << e << " as been found inside the list container" << std::endl;
	}
	try
	{
		int result = easyfind(deque, 42);
		std::cout << "An occurence of " << result << " has been found inside the deque container" << std::endl;
	}
	catch(const int e)
	{
		std::cout << "Zero occurence of " << e << " as been found inside the deque container" << std::endl;
	}
	return (0);
}
