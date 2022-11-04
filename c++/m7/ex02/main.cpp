#include "Array.hpp"

int main()
{
	Array<int> test(2);
	Array<int> test2(2);
	try
	{
		for (unsigned int i = 0 ; i < test.size() ; i++)
			test[i] = i;
		std::cout << "First array: (size = " << test.size() << ")" << std::endl;
		for (unsigned int i = 0 ; i < test.size() ; i++)
			std::cout << test[i] << std::endl;
		for (unsigned int i = 0 ; i < test2.size() ; i++)
			test2[i] = i + 100;
		std::cout << "Second array:" << std::endl;
		for (unsigned int i = 0 ; i < test2.size() ; i++)
			std::cout << test2[i] << std::endl;
		test = test2;
		std::cout << "First array after using assignment operator with second array as source:" << std::endl;
		for (unsigned int i = 0 ; i < test.size() ; i++)
			std::cout << test[i] << std::endl;
		std::cout << "Modifying second array:" << std::endl;
		for (unsigned int i = 0 ; i < test2.size() ; i++)
			test2[i] = i + 200;
		for (unsigned int i = 0 ; i < test2.size() ; i++)
			std::cout << test2[i] << std::endl;
		std::cout << "First array didn't change:" << std::endl;
		for (unsigned int i = 0 ; i < test.size() ; i++)
			std::cout << test[i] << std::endl;
		Array<int> test3(test2);
		std::cout << "Testing copy constructor with second array as parameter:" << std::endl;
		for (unsigned int i = 0 ; i < test3.size() ; i++)
			std::cout << test3[i] << std::endl;
		std::cout << "Using incorrect index:" << std::endl;
		std::cout << test[99] << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Array::InvalidIndexException" << std::endl;
	}
	return (0);
}
