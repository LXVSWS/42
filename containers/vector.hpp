#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "iterator.hpp"
#include "utils.hpp"

namespace ft
{
	template < typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:
			class Iterator : public ft::iterator<random_access_iterator_tag, T>
			{
				T *ptr;

				public:
					Iterator(T *data) : ptr(data) {}
					Iterator(const Iterator& src) : ptr(src.ptr) {}
					T& operator*() { return (*ptr); }
					Iterator& operator++() { ++ptr; return (*this); }
					Iterator operator++(T) { Iterator tmp(*this); ++ptr; return (tmp); }
  					bool operator==(const Iterator& src) const { return ptr == src.ptr; }
  					bool operator!=(const Iterator& src) const { return ptr != src.ptr; }
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
			: allocator(alloc), _capacity(1), _size(0)
			{
				data = allocator.allocate(1);
			}
			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) \
			: allocator(alloc), _capacity(n > 0 ? n : 1), _size(n)
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
			vector(Iterator first, Iterator last, const allocator_type& alloc = allocator_type()) \
			: allocator(alloc), _capacity(1), _size(0)
			{
				data = allocator.allocate(1);
				(void)first;
				(void)last;
			}
			vector(const vector& src) \
			: _capacity(src._capacity), _size(src._size)
			{
				data = allocator.allocate(src._capacity);
				for (size_t i = 0 ; i < src._size ; i++)
					data[i] = src.data[i];
			}
			~vector()
			{
				allocator.deallocate(data, _capacity);
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
				T tmp[_size];

				if (n > _capacity)
				{
					for (size_t i = 0 ; i < _size ; i++)
						tmp[i] = data[i];
					allocator.deallocate(data, _capacity);
					data = allocator.allocate(n, data);
					_capacity = n;
					for (size_t i = 0 ; i < _size ; i++)
						data[i] = tmp[i];
				}
			}
			value_type *data()
			{
				return (data);
			}
			const value_type *data() const
			{
				return (data);
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
			size_t _capacity;
			size_t _size;
	};
}

#endif
