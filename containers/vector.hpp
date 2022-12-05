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
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef Iterator<value_type> iterator;
			typedef ConstIterator<value_type> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;

			vector() : _capacity(1), _size(0)
			{
				_data = allocator.allocate(1);
			}
			explicit vector(const Alloc& alloc) \
			: allocator(alloc), _capacity(1), _size(0)
			{
				_data = allocator.allocate(1);
			}
			explicit vector(size_t n, const T& val = T(), const Alloc& alloc = Alloc()) \
			: allocator(alloc), _capacity(n > 0 ? n : 1), _size(n)
			{
				if (n)
				{
					_data = allocator.allocate(n);
					for (size_t i = 0 ; i < n ; i++)
						allocator.construct(&_data[i], val);
				}
				else
					_data = allocator.allocate(1);
			}
			template <typename InputIterator>
			vector(InputIterator first, InputIterator last, const Alloc& alloc) : allocator(alloc)
			{
				size_t n = 0;
				for (ft::vector<int>::iterator i = first ; i != last ; ++i)
					n++;
				if (n)
					_data = allocator.allocate(n);
				else
				{
					_data = allocator.allocate(1);
					_capacity = 1;
					_size = 0;
					return ;
				}
				_capacity = n;
				n = 0;
				for (ft::vector<int>::iterator i = first ; i != last ; ++i)
					allocator.construct(&_data[n++], *i);
				_size = n;
			}
			vector(const vector& src) : _capacity(src._capacity), _size(src._size)
			{
				_data = allocator.allocate(src._capacity);
				for (size_t i = 0 ; i < src._size ; i++)
					allocator.construct(&_data[i], src._data[i]);
			}
			~vector()
			{
				for (size_t i = 0 ; i < _size ; i++)
					allocator.destroy(&_data[i]);
				allocator.deallocate(_data, _capacity);
				_data = NULL;
			}
			vector& operator=(const vector& src)
			{
				if (this != &src)
				{
					for (size_t i = 0 ; i < _size ; i++)
						allocator.destroy(&_data[i]);
					if (src._size > _capacity)
						reserve(src._size * 2);
					for (size_t i = 0 ; i < src._size ; i++)
						allocator.construct(&_data[i], src._data[i]);
					_size = src._size;
				}
				return (*this);
			}
			iterator begin()
			{
				iterator i(_data);
				return (i);
			}
			const_iterator begin() const
			{
				const_iterator i(_data);
				return (i);
			}
			iterator end()
			{
				iterator i(&_data[_size]);
				return (i);
			}
			const_iterator end() const
			{
				const_iterator i(&_data[_size]);
				return (i);
			}
			reverse_iterator rbegin()
			{
				reverse_iterator i(&_data[_size - 1]);
				return (i);
			}
			const_reverse_iterator rbegin() const
			{
				const_reverse_iterator i(&_data[_size - 1]);
				return (i);
			}
			reverse_iterator rend()
			{
				reverse_iterator i(&_data[-1]);
				return (i);
			}
			const_reverse_iterator rend() const
			{
				const_reverse_iterator i(&_data[-1]);
				return (i);
			}
			size_type size() const
			{
				return (_size);
			}
			size_type max_size() const
			{
				return (allocator.max_size());
			}
			//void resize(size_type n, value_type val = value_type()) {}
			size_type capacity() const
			{
				return (_capacity);
			}
			bool empty() const
			{
				if (!_size)
					return (true);
				return (false);
			}
			void reserve(size_type n)
			{
				T tmp[_size];

				if (n > _capacity)
				{
					for (size_t i = 0 ; i < _size ; i++)
					{
						tmp[i] = _data[i];
						allocator.destroy(&_data[i]);
					}
					allocator.deallocate(_data, _capacity);
					_data = allocator.allocate(n, _data);
					_capacity = n;
					for (size_t i = 0 ; i < _size ; i++)
						allocator.construct(&_data[i], tmp[i]);
				}
			}
			T *data()
			{
				return (_data);
			}
			const T *data() const
			{
				return (_data);
			}
			void push_back(const T &val)
			{
				if (_size == _capacity)
					reserve(_capacity * 2);
				allocator.construct(&_data[_size], val);
				_size++;
			}
			allocator_type get_allocator() const
			{
				return (allocator);
			}

		private:
			T *_data;
			Alloc allocator;
			size_t _capacity;
			size_t _size;
	};
}

#endif
