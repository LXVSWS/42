#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag {};
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};

	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template <class Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
			typedef typename iterator_traits<Iterator>::value_type value_type;
			typedef typename iterator_traits<Iterator>::difference_type difference_type;
			typedef typename iterator_traits<Iterator>::pointer pointer;
			typedef typename iterator_traits<Iterator>::reference reference;
	};

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
}

#endif
