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
			class Iterator : public ft::iterator<random_access_iterator_tag, T>
			{
				T *data;

				public:
					Iterator(T *data) : data(data) {}
					T& operator*() { return (*data); }
					T& operator=(T& src) { data = src.data; }
			};

			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef Iterator iterator;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;

			explicit vector(const allocator_type& alloc = allocator_type())
			{
				allocator = alloc;
				data = allocator.allocate(1);
				original_capacity = 1;
				_capacity = 1;
				_size = 0;
			}
			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			{
				allocator = alloc;
				if (n)
				{
					data = allocator.allocate(n);
					original_capacity = n;
					_capacity = n;
					for (size_t i = 0 ; i < n ; i++)
						data[i] = val;
					_size = n;
				}
				else
				{
					data = allocator.allocate(1);
					original_capacity = 1;
					_capacity = 1;
					*data = val;
					_size = 0;
				}
			}
			vector(const vector& src)
			{
				allocator = src.allocator;
				data = allocator.allocate(src._capacity);
				original_capacity = src._capacity;
				_capacity = src._capacity;
				for (size_t i = 0 ; i < src._size ; i++)
					data[i] = (src.data)[i];
				_size = src._size;
			}
			~vector()
			{
				allocator.deallocate(data, original_capacity);
			}
			iterator begin()
			{
				iterator i(data);
				return (i);
			}
			iterator end()
			{
				iterator i(&data[_size]);
				return (i);
			}
			size_type size() const
			{
				return (_size);
			}
			size_type capacity() const
			{
				return (_capacity);
			}
			void reserve(size_type n)
			{
				if (n > _capacity)
				{
					data = allocator.allocate(n);
					_capacity = n;
				}
			}
			void push_back(const value_type& val)
			{
				if (_size == _capacity)
					reserve(_capacity * 2);
				data[_size] = val;
				_size++;
			}

		private:
			T *data;
			Alloc allocator;
			size_t original_capacity;
			size_t _capacity;
			size_t _size;
	};
}

#endif
