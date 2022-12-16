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

			explicit vector(const Alloc& alloc = Alloc()) \
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
			vector(typename std::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type first, // replace by own implementations
			InputIterator last, const Alloc& alloc = Alloc()) : allocator(alloc)
			{
				size_t n = 0;
				for (InputIterator i = first ; i != last ; ++i)
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
				for (InputIterator i = first ; i != last ; ++i)
					allocator.construct(&_data[n++], *i);
				_size = n;
			}
			vector(const vector& src) : allocator(src.allocator), _capacity(src._capacity), _size(src._size)
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
						reserve(src._size);
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
				reverse_iterator i(end());
				return (i);
			}
			const_reverse_iterator rbegin() const
			{
				const_reverse_iterator i(end());
				return (i);
			}
			reverse_iterator rend()
			{
				reverse_iterator i(begin());
				return (i);
			}
			/*
			const_reverse_iterator rend() const
			{
				const_reverse_iterator i(begin());
				return (i);
			}
			*/
			size_type size() const
			{
				return (_size);
			}
			size_type max_size() const
			{
				return (allocator.max_size());
			}
			void resize(size_type n, value_type val = T())
			{
				if (n < _size)
				{
					for (size_t i = n ; i < _size ; i++)
						allocator.destroy(&_data[i]);
					_size = n;
				}
				else if (n > _size)
				{
					if (n > _capacity)
						reserve(n);
					for (size_t i = _size ; i < n ; i++)
						allocator.construct(&_data[i], val);
					_size = n;
				}
			}
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
			reference operator[](size_type n)
			{
				return (_data[n]);
			}
			const_reference operator[](size_type n) const
			{
				return (_data[n]);
			}
			reference at(size_type pos)
			{
				if (!(pos < _size))
					throw std::out_of_range("Exception::OutOfRange");
				return (_data[pos]);
			}
			const_reference at(size_type pos) const
			{
				if (!(pos < _size))
					throw std::out_of_range("Exception::OutOfRange");
				return (_data[pos]);
			}
			reference front()
			{
				return (*_data);
			}
			const_reference front() const
			{
				return (*_data);
			}
			reference back()
			{
				return (_data[_size - 1]);
			}
			const_reference back() const
			{
				return (_data[_size - 1]);
			}
			T *data()
			{
				return (_data);
			}
			const T *data() const
			{
				return (_data);
			}
			template <typename InputIterator>
			typename std::enable_if<!std::is_integral<InputIterator>::value>::type // replace by own implementations
			assign(InputIterator first, InputIterator last)
			{
				for (size_t i = 0 ; i < _size ; i++)
					allocator.destroy(&_data[i]);
				size_t n = 0;
				for (InputIterator i = first ; i != last ; ++i)
					n++;
				if (n > _capacity)
				{
					reserve(n);
					_capacity = n;
				}
				n = 0;
				for (InputIterator i = first ; i != last ; ++i)
					allocator.construct(&_data[n++], *i);
				_size = n;
			}
			void assign(size_type n, const value_type& val)
			{
				for (size_t i = 0 ; i < _size ; i++)
					allocator.destroy(&_data[i]);
				if (n > _capacity)
				{
					reserve(n);
					_capacity = n;
				}
				for (size_t i = 0 ; i < n ; i++)
					allocator.construct(&_data[i], val);
				_size = n;
			}
			void push_back(const T &val)
			{
				if (_size == _capacity)
					reserve(_capacity * 2);
				allocator.construct(&_data[_size], val);
				_size++;
			}
			void pop_back()
			{
				allocator.destroy(&_data[_size - 1]);
				_size--;
			}
			//iterator insert(iterator position, const value_type& val) {}
			void clear()
			{
				for (size_t i = 0 ; i < _size ; i++)
					allocator.destroy(&_data[i]);
				_size = 0;
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
