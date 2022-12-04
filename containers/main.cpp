#include "vector.hpp"
#include "map.hpp"
#include "utils.hpp"

int main()
{
	try
	{
		ft::vector<int> test0;
		std::cout << "Default constructor\nSize : " << test0.size() << std::endl;
		std::cout << "Capacity : " << test0.capacity() << std::endl;

		ft::vector<int> test1(0);
		std::cout << "\nFill constructor (1)\nSize : " << test1.size() << std::endl;
		std::cout << "Capacity : " << test1.capacity() << std::endl;
		for (ft::vector<int>::iterator i = test1.begin() ; i != test1.end() ; ++i)
			std::cout << *i << std::endl;

		ft::vector<int> test(2, 42);
		std::cout << "\nFill constructor (2, 42)" << std::endl;
		std::cout << "Data : " << test.data() << std::endl;
		std::cout << "Size : " << test.size() << std::endl;
		std::cout << "Capacity : " << test.capacity() << std::endl;
		for (ft::vector<int>::iterator i = test.begin() ; i != test.end() ; ++i)
			std::cout << *i << std::endl;

		std::allocator<int> tes;
		ft::vector<int> test3(test.begin(), test.end(), tes);
		std::cout << "\nRange constructor" << std::endl;
		std::cout << "Data : " << test3.data() << std::endl;
		std::cout << "Size : " << test3.size() << std::endl;
		std::cout << "Capacity : " << test3.capacity() << std::endl;
		for (ft::vector<int>::iterator i = test3.begin() ; i != test3.end() ; ++i)
			std::cout << *i << std::endl;

		ft::vector<int> test2(test);
		std::cout << "\nCopy constructor\nData : " << test2.data() << std::endl;
		std::cout << "Size : " << test2.size() << std::endl;
		std::cout << "Capacity : " << test2.capacity() << std::endl;
		for (ft::vector<int>::iterator i = test2.begin() ; i != test2.end() ; ++i)
			std::cout << *i << std::endl;

		test.push_back(66);
		std::cout << "\nPush_back (66) member function" << std::endl;
		std::cout << "Data : " << test.data() << std::endl;
		std::cout << "Size : " << test.size() << std::endl;
		std::cout << "Capacity : " << test.capacity() << std::endl;
		for (ft::vector<int>::iterator i = test.begin() ; i != test.end() ; ++i)
			std::cout << *i<< std::endl;

		test.reserve(5);
		std::cout << "\nReserve (5) member function" << std::endl;
		std::cout << "Data : " << test.data() << std::endl;
		std::cout << "Size : " << test.size() << std::endl;
		std::cout << "Capacity : " << test.capacity() << std::endl;

		test2 = test;
		std::cout << "\nAssign operator\nData : " << test2.data() << std::endl;
		std::cout << "Size : " << test2.size() << std::endl;
		std::cout << "Capacity : " << test2.capacity() << std::endl;
		for (ft::vector<int>::iterator i = test2.begin() ; i != test2.end() ; ++i)
			std::cout << *i << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
