#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>

namespace ft
{
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class iterator
	{
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag {};
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};

	template <typename T>
	class ConstIterator : public iterator<random_access_iterator_tag, const T>
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

	template <typename T>
	class Iterator : public iterator<random_access_iterator_tag, T>
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
			operator ConstIterator<T>() const { ConstIterator<T> src = ptr; return(src); }
	};

	template <class Iterator>
	class iterator_traits
	{
	};

	template <class T>
	class iterator_traits<T*>
	{
	};

	template <class T>
	class iterator_traits<const T*>
	{
	};

	template <class Iterator>
	class reverse_iterator
	{
	};
}

#endif
