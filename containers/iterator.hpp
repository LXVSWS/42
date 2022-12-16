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
		typedef const T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template <typename T>
	class ConstIterator : public iterator<random_access_iterator_tag, const T>
	{
		private:
			const T* ptr;
		public:
			ConstIterator() : ptr(NULL) {}
			ConstIterator(const T *src) : ptr(src) {}
			ConstIterator(const ConstIterator& src) : ptr(src.ptr) {}
			ConstIterator& operator=(const ConstIterator& src) { ptr = src.ptr; return (*this); }
			~ConstIterator() {};
			const T& operator*() const { return (*ptr); }
			ConstIterator& operator++() { ++ptr; return (*this); }
			ConstIterator operator++(T) { ConstIterator tmp(*this); ++ptr; return (tmp); }
			ConstIterator& operator--() { --ptr; return (*this); }
			ConstIterator operator--(T) { ConstIterator tmp(*this); --ptr; return (tmp); }
			ConstIterator operator+(const T& n) const { return (ConstIterator(ptr + n)); }
			ConstIterator& operator+=(const T& n) { ptr += n; return (*this); }
			ConstIterator operator-(const T& n) const { return (ConstIterator(ptr - n)); }
			ConstIterator& operator-=(const T& n) { ptr -= n; return (*this); }
			bool operator==(const ConstIterator& src) const { return ptr == src.ptr; }
			bool operator!=(const ConstIterator& src) const { return ptr != src.ptr; }
	};

	template <typename T>
	class Iterator : public iterator<random_access_iterator_tag, T>
	{
		private:
			T* ptr;
		public:
			Iterator() : ptr(NULL) {}
			Iterator(T *src) : ptr(src) {}
			Iterator(const Iterator& src) : ptr(src.ptr) {}
			Iterator& operator=(const Iterator& src) { ptr = src.ptr; return (*this); }
			~Iterator() {};
			T& operator*() const { return (*ptr); }
			Iterator& operator++() { ++ptr; return (*this); }
			Iterator operator++(T) { Iterator tmp(*this); ++ptr; return (tmp); }
			Iterator& operator--() { --ptr; return (*this); }
			Iterator operator--(T) { Iterator tmp(*this); --ptr; return (tmp); }
			Iterator operator+(const T& n) const { return (Iterator(ptr + n)); }
			Iterator& operator+=(const T& n) { ptr += n; return (*this); }
			Iterator operator-(const T& n) const { return (Iterator(ptr - n)); }
			Iterator& operator-=(const T& n) { ptr -= n; return (*this); }
			bool operator==(const Iterator& src) const { return (ptr == src.ptr); }
			bool operator!=(const Iterator& src) const { return (ptr != src.ptr); }
			operator ConstIterator<T>() const { ConstIterator<T> src = ptr; return(src); }
	};

	template <class Iterator>
	class reverse_iterator
	{
		protected:
			Iterator current;
		public:
			typedef Iterator iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
			typedef typename iterator_traits<Iterator>::value_type value_type;
			typedef typename iterator_traits<Iterator>::difference_type difference_type;
			typedef typename iterator_traits<Iterator>::pointer pointer;
			typedef typename iterator_traits<Iterator>::reference reference;

			reverse_iterator() : current(Iterator()) {}
			explicit reverse_iterator(iterator_type it) : current(it) { --current; }
			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter>& rev_it) { this->current = rev_it.current; }
			iterator_type base() const { return (current); }
			reference operator*() const { return (*current); }
			reverse_iterator& operator++() { --current; return (*this); }
			reverse_iterator operator++(int) { reverse_iterator tmp(*this); --current; return (tmp); }
			reverse_iterator& operator--() { ++current; return (*this); }
			reverse_iterator operator--(int) { reverse_iterator tmp(*this); ++current; return (tmp); }
			reverse_iterator operator+(const value_type& n) const { return (reverse_iterator(current - n)); }
			reverse_iterator& operator+=(const value_type& n) { current -= n; return (*this); }
			reverse_iterator operator-(const value_type& n) const { return (reverse_iterator(current + n)); }
			reverse_iterator& operator-=(const value_type& n) { current += n; return (*this); }
		private:
			value_type* ptr;
	};
}

#endif
