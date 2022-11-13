#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <vector>

namespace ft
{
	template<typename T>
	class vector
	{
		public:
			vector()
			{
				std::cout << "vector container constructor" << std::endl;
			}
			~vector()
			{
				std::cout << "vector container destructor" << std::endl;
			}
	};
}

#endif
