#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "iterator.hpp"

namespace ft
{
	template< typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:

			struct Iterator : public iterator<random_access_iterator_tag, T>
			{
				T *ptr;
				friend std::ostream &operator<<(std::ostream& dst, const Iterator& src)
				{
					dst << src.ptr;
					return (dst);
				}
			};

			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef Iterator iterator;
			typedef reverse_iterator<iterator> reverse_iterator;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;

			explicit vector(const allocator_type& alloc = allocator_type())
			{
				allocator = alloc;
				data = allocator.allocate(1);
				original_capacity = 1;
				capacity = 1;
				size = 0;
			}
			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			{
				allocator = alloc;
				if (n)
				{
					data = allocator.allocate(n);
					original_capacity = n;
					capacity = n;
					for (size_t i = 0 ; i < n ; i++)
						data[i] = val;
					size = n;
				}
				else
				{
					data = allocator.allocate(1);
					original_capacity = 1;
					capacity = 1;
					*data = val;
					size = 0;
				}
			}
			vector(const vector& src)
			{
				allocator = src.allocator;
				data = allocator.allocate(src.capacity);
				original_capacity = src.capacity;
				capacity = src.capacity;
				for (size_t i = 0 ; i < src.size ; i++)
					data[i] = (src.data)[i];
				size = src.size;
			}
			~vector()
			{
				allocator.deallocate(data, original_capacity);
			}
			iterator begin()
			{
				iterator i;
				i.ptr = data;
				return (i);
			}
			void reserve(size_type n)
			{
				if (n > capacity)
				{
					data = allocator.allocate(n);
					capacity = n;
				}
			}

		private:
			Alloc allocator;
			value_type *data;
			size_t original_capacity;
			size_t capacity;
			size_t size;
	};
}

#endif
