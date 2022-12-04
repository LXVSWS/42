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
			class ConstIterator : public ft::iterator<random_access_iterator_tag, const T>
			{
				const T *ptr;

				public:
					ConstIterator(const T *src) : ptr(src) {}
					ConstIterator(const ConstIterator& src) : ptr(src.ptr) {}
					const T& operator*() const { return (*ptr); }
					ConstIterator& operator++() { ++ptr; return (*this); }
					ConstIterator operator++(T) { ConstIterator tmp(*this); ++ptr; return (tmp); }
  					bool operator==(const ConstIterator& src) const { return ptr == src.ptr; }
  					bool operator!=(const ConstIterator& src) const { return ptr != src.ptr; }
			};

			class Iterator : public ft::iterator<random_access_iterator_tag, T>
			{
				T *ptr;

				public:
					Iterator(T *src) : ptr(src) {}
					Iterator(const Iterator& src) : ptr(src.ptr) {}
					T& operator*() const { return (*ptr); }
					Iterator& operator++() { ++ptr; return (*this); }
					Iterator operator++(T) { Iterator tmp(*this); ++ptr; return (tmp); }
  					bool operator==(const Iterator& src) const { return (ptr == src.ptr); }
  					bool operator!=(const Iterator& src) const { return (ptr != src.ptr); }
					operator ConstIterator() const { ConstIterator src = ptr; return(src); }
			};

			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef Iterator iterator;
			typedef ConstIterator const_iterator;
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
						_data[i] = val;
				}
				else
				{
					_data = allocator.allocate(1);
					*_data = val;
				}
			}
			//template <InputIt> vector(InputIt first, InputIt last, const Alloc& alloc = Alloc()) : allocator(alloc) {}
			vector(const vector& src) : _capacity(src._capacity), _size(src._size)
			{
				_data = allocator.allocate(src._capacity);
				for (size_t i = 0 ; i < src._size ; i++)
					_data[i] = src._data[i];
			}
			~vector()
			{
				allocator.deallocate(_data, _capacity);
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
						tmp[i] = _data[i];
					allocator.deallocate(_data, _capacity);
					_data = allocator.allocate(n, _data);
					_capacity = n;
					for (size_t i = 0 ; i < _size ; i++)
						_data[i] = tmp[i];
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
				_data[_size] = val;
				_size++;
			}

		private:
			T *_data;
			Alloc allocator;
			size_t _capacity;
			size_t _size;
	};
}

#endif
