#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <vector>

namespace ft
{
	template< typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		private:
			T *data;
			Alloc allocator;
			size_t original_size;

		public:
			vector() {}
			~vector()
			{
				allocator.deallocate(data, original_size);
			}
			void reserve(size_t size)
			{
				original_size = size;
				data = allocator.allocate(size);
			}

	};
}

#endif
