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
		private:
			T *_data;
			Alloc allocator;
			size_t _capacity;
			size_t _size;
		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef random_access_iterator<value_type> iterator;
			typedef random_access_iterator<const value_type> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef std::ptrdiff_t difference_type;
			typedef std::size_t size_type;

			explicit vector(const Alloc& alloc = Alloc()) \
			: allocator(alloc), _capacity(1), _size(0)
			{
				_data = allocator.allocate(1);
			}
			explicit vector(size_t n, const T& val = value_type(), const Alloc& alloc = Alloc()) \
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
			vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
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
			const_reverse_iterator rend() const
			{
				const_reverse_iterator i(begin());
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
			void resize(size_type n, value_type val = value_type())
			{
				if (n == _size)
					return ;
				if (n > _capacity) //
					reserve(n);
				while (n > _size)
					push_back(val);
				while (n < _size)
					pop_back();
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

				if (n > max_size())
					throw std::length_error("allocator max size overflow");
				if (n > _capacity)
				{
					for (size_t i = 0 ; i < _size ; i++)
					{
						tmp[i] = _data[i];
						allocator.destroy(&_data[i]);
					}
					allocator.deallocate(_data, _capacity);
					_data = allocator.allocate(n);
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
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type
			assign(InputIterator first, InputIterator last)
			{
				clear();
				size_t n = 0;
				for (InputIterator i = first ; i != last ; ++i)
					n++;
				if (n > _capacity)
					reserve(n);
				n = 0;
				for (InputIterator i = first ; i != last ; ++i)
					allocator.construct(&_data[_size++], *i);
			}
			void assign(size_type n, const value_type& val)
			{
				clear();
				if (n > _capacity)
					reserve(n);
				for (size_t i = 0 ; i < n ; i++)
					allocator.construct(&_data[i], val);
				_size = n;
			}
			void push_back(const T &val)
			{
				if (_size >= _capacity)
					reserve(_capacity * 2);
				allocator.construct(&_data[_size], val);
				_size++;
			}
			void pop_back()
			{
				allocator.destroy(&_data[_size - 1]);
				_size--;
			}
			iterator insert(iterator position, const value_type& val)
			{
				if (position == end())
				{
					push_back(val);
					return (position);
				}
				T tmp[_size];
				size_t i = 0;
				size_t j = 0;
				for (typename ft::vector<T>::iterator it = position ; it != end() ; ++it)
					tmp[i++] = *it;
				for (typename ft::vector<T>::iterator it = begin() ; it != position ; ++it)
					j++;
				for (size_t k = j ; k < i + j ; k++)
				{
					allocator.destroy(&_data[k]);
					_size--;
				}
				push_back(val);
				for (size_t k = 0 ; k < i ; k++)
					push_back(tmp[k]);
				return (position);
			}
			void insert(iterator position, size_type n, const value_type& val)
			{
				if (position == end())
				{
					for (size_t i = 0 ; i < n ; ++i)
						push_back(val);
					return ;
				}
				T tmp[_size];
				size_t i = 0;
				size_t j = 0;
				for (typename ft::vector<T>::iterator it = position ; it != end() ; ++it)
					tmp[i++] = *it;
				for (typename ft::vector<T>::iterator it = begin() ; it != position ; ++it)
					j++;
				if (_size + n > _capacity)
					reserve(_capacity + n);
				for (size_t k = j ; k < i + j ; k++)
				{
					allocator.destroy(&_data[k]);
					_size--;
				}
				for (size_t k = 0 ; k < n ; k++)
					push_back(val);
				for (size_t k = 0 ; k < i ; k++)
					push_back(tmp[k]);
			}
			template <class InputIterator>
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type
			insert(iterator position, InputIterator first, InputIterator last)
			{
				if (position == end())
				{
					for (InputIterator i = first ; i != last ; ++i)
						push_back(*i);
					return ;
				}
				T tmp[_size];
				size_t i = 0;
				size_t j = 0;
				for (typename ft::vector<T>::iterator it = position ; it != end() ; ++it)
					tmp[i++] = *it;
				for (typename ft::vector<T>::iterator it = begin() ; it != position ; ++it)
					j++;
				size_t n = 0;
				for (InputIterator i = first ; i != last ; ++i)
					n++;
				if (_size + n > _capacity) //
					reserve(_capacity + n);
				for (size_t k = j ; k < i + j ; k++)
				{
					allocator.destroy(&_data[k]);
					_size--;
				}
				n = 0;
				for (InputIterator it = first ; it != last ; ++it)
					allocator.construct(&_data[_size++], *it);
				for (size_t k = 0 ; k < i ; k++)
					push_back(tmp[k]);
			}
			iterator erase(iterator position)
			{
				if (position == end() || !*position)
					return (position);
				if (position == end() - 1)
				{
					pop_back();
					return (end());
				}
				T tmp[_size];
				size_t i = 0;
				typename ft::vector<T>::iterator ret = position - 1;
				for (typename ft::vector<T>::iterator it = position + 1 ; it != end() ; ++it)
				{
					tmp[i++] = *it;
					allocator.destroy(&*it);
				}
				_size -= i;
				pop_back();
				for (size_t j = 0 ; j < i ; ++j)
					push_back(tmp[j]);
				return (++ret);
			}
			iterator erase(iterator first, iterator last)
			{
				if (first == end() || !*first)
					return (first);
				if (first == end() - 1 && last == end())
				{
					pop_back();
					return (end());
				}
				T tmp[_size];
				size_t i = 0;
				typename ft::vector<T>::iterator ret = first - 1;
				for (typename ft::vector<T>::iterator it = last ; it != end() ; ++it)
				{
					tmp[i++] = *it;
					allocator.destroy(&*it);
				}
				_size -= i;
				while (first != last)
				{
					allocator.destroy(&*first);
					++first;
					_size--;
				}
				for (size_t j = 0 ; j < i ; ++j)
					push_back(tmp[j]);
				return (++ret);
			}
			void swap(vector& x)
			{
				if (x == *this)
					return ;
				T *_data_tmp = x.data();
				Alloc allocator_tmp = x.get_allocator();
				size_t _capacity_tmp = x.capacity();
				size_t _size_tmp = x.size();
				x._data = _data;
				x.allocator = allocator;
				x._capacity = _capacity;
				x._size = _size;
				_data = _data_tmp;
				allocator = allocator_tmp;
				_capacity = _capacity_tmp;
				_size = _size_tmp;
			}
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
	};

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() == rhs.size())
		{
			for (size_t i = 0 ; i < lhs.size() ; ++i)
				if (lhs[i] != rhs[i])
					return (false);
			return (true);
		}
		return (false);
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (!(lhs == rhs))
			return (true);
		return (false);
	}

	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
