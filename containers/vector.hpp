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

			explicit vector(const allocator_type& alloc = allocator_type()) \
			: allocator(alloc), original_capacity(1), _capacity(1), _size(0)
			{
				data = allocator.allocate(1);
			}
			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) \
			: allocator(alloc), original_capacity(n > 0 ? n : 1), _capacity(n > 0 ? n : 1), _size(n)
			{
				if (n)
				{
					data = allocator.allocate(n);
					for (size_t i = 0 ; i < n ; i++)
						data[i] = val;
				}
				else
				{
					data = allocator.allocate(1);
					*data = val;
				}
			}
			template<class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) \
			: allocator(alloc), original_capacity(1), _capacity(1), _size(0)
			{
				data = allocator.allocate(1);
				(void)first;
				(void)last;
			}
			vector(const vector& src) \
			: original_capacity(src._capacity), _capacity(src._capacity), _size(src._size)
			{
				data = allocator.allocate(src._capacity);
				for (size_t i = 0 ; i < src._size ; i++)
					data[i] = (src.data)[i];
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
			size_type original_capacityy() const
			{
				return (original_capacity);
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
			const size_t original_capacity;
			size_t _capacity;
			size_t _size;
	};
}

#endif
