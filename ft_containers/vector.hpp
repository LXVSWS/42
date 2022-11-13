#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <vector>

namespace ft
{
	template< typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:
			vector()
			{
				std::cout << "vector constructor" << std::endl;
			}
			~vector()
			{
				std::cout << "vector destructor" << std::endl;
			}
	};
}

#endif
