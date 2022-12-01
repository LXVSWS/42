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
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;

			explicit vector(const allocator_type& alloc = allocator_type())
			{
				allocator = alloc;
				data = allocator.allocate(1);
				this->original_capacity = 1;
				this->capacity = 1;
			}
			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			{
				if (n)
				{
					allocator = alloc;
					data = allocator.allocate(n);
					this->original_capacity = n;
					this->capacity = n;
					for (size_t i = 0 ; i < n ; i++)
						data[i] = val;
				}
				else
				{
					allocator = alloc;
					data = allocator.allocate(1);
					this->original_capacity = 1;
					this->capacity = 1;
				}
			}
			/*
			template <class InputIterator>vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
			{

			}
			vector (const vector& x)
			{

			}
			*/
			~vector()
			{
				allocator.deallocate(data, this->original_capacity);
			}
			void reserve(size_t size)
			{
				if (size > this->capacity)
				{
					data = allocator.allocate(size);
					this->capacity = size;
				}
			}

		private:
			T *data;
			Alloc allocator;
			size_t original_capacity;
			size_t capacity;

			friend std::ostream &operator<<(std::ostream& dst, const vector& src)
			{
				dst << src.capacity;
				return (dst);
			}
	};
}

#endif
