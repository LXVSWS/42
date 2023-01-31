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
			explicit reverse_iterator(Iterator it) : current(it) {}
			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter>& rev_it) { this->current = rev_it.base(); }

			Iterator base() const { return (current); }
			reference operator*() const { Iterator tmp(current); --tmp; return (*tmp); }
			reverse_iterator& operator++() { --current; return (*this); }
			reverse_iterator operator++(int) { reverse_iterator tmp(*this); --current; return (tmp); }
			reverse_iterator& operator--() { ++current; return (*this); }
			reverse_iterator operator--(int) { reverse_iterator tmp(*this); ++current; return (tmp); }
			reverse_iterator& operator+=(difference_type n) { current -= n; return (*this); }
			reverse_iterator& operator-=(difference_type n) { current += n; return (*this); }
			pointer operator->() const { return &(operator*()); }
			reference operator[] (difference_type n) const { return (current[-n-1]); }
			operator reverse_iterator<iterator_type const>() const { return reverse_iterator<iterator_type const>(current); }
	};

	template <class Iterator>
	reverse_iterator<Iterator>
	operator+(const reverse_iterator<Iterator>& lhs, typename reverse_iterator<Iterator>::difference_type n) {
		return reverse_iterator<Iterator>(lhs.base() - n); }

	template <class Iterator>
	reverse_iterator<Iterator>
	operator-(const reverse_iterator<Iterator>& lhs, typename reverse_iterator<Iterator>::difference_type n) {
		return reverse_iterator<Iterator>(lhs.base() + n); }

	template <class Iterator>
	reverse_iterator<Iterator>
	operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rhs) {
		return reverse_iterator<Iterator>(rhs.base() - n); }

	template <class Iterator>
	reverse_iterator<Iterator>
	operator-(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rhs) {
		return reverse_iterator<Iterator>(rhs.base() + n); }

	template <typename Iterator1, typename Iterator2>
	typename reverse_iterator<Iterator1>::difference_type
	operator+(reverse_iterator<Iterator1> const & lhs, reverse_iterator<Iterator2> const & rhs) {
		return (lhs.base() + rhs.base()); }

	template <typename Iterator1, typename Iterator2>
	typename reverse_iterator<Iterator1>::difference_type
	operator-(reverse_iterator<Iterator1> const & lhs, reverse_iterator<Iterator2> const & rhs) {
		return (rhs.base() - lhs.base()); }

	template <typename Iterator1, typename Iterator2>
	bool operator==(const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs) {
		return ((lhs.base() == rhs.base())); }

	template <typename Iterator1, typename Iterator2>
	bool operator!=(reverse_iterator<Iterator1> const & lhs, reverse_iterator<Iterator2> const & rhs) {
		return (!(lhs == rhs)); }

	template <typename Iterator1, typename Iterator2>
	bool operator<(reverse_iterator<Iterator1> const & lhs, reverse_iterator<Iterator2> const & rhs) {
		return ((lhs.base() > rhs.base())); }

	template <typename Iterator1, typename Iterator2>
	bool operator<=(reverse_iterator<Iterator1> const & lhs, reverse_iterator<Iterator2> const & rhs) {
		return ((lhs == rhs || lhs < rhs)); }

	template <typename Iterator1, typename Iterator2>
	bool operator>(reverse_iterator<Iterator1> const & lhs, reverse_iterator<Iterator2> const & rhs) {
		return (!(lhs <= rhs)); }

	template <typename Iterator1, typename Iterator2>
	bool operator>=(reverse_iterator<Iterator1> const & lhs, reverse_iterator<Iterator2> const & rhs) {
		return (!(lhs < rhs)); }

	template <typename T>
	class random_access_iterator : public iterator<random_access_iterator_tag, T>
	{
		private:
			T* ptr;
		public:
			typedef iterator<random_access_iterator_tag, T> iterator_type;
			typedef typename iterator_traits<random_access_iterator>::value_type		value_type;
			typedef typename iterator_traits<random_access_iterator>::difference_type	difference_type;
			typedef typename iterator_traits<random_access_iterator>::pointer			pointer;
			typedef typename iterator_traits<random_access_iterator>::reference			reference;
			typedef typename iterator_traits<random_access_iterator>::iterator_category	iterator_category;

			random_access_iterator() : ptr(NULL) {}
			random_access_iterator(T *src) : ptr(src) {}
			random_access_iterator(const random_access_iterator& src) : ptr(src.ptr) {}
			random_access_iterator& operator=(const random_access_iterator& src) { ptr = src.ptr; return (*this); }
			~random_access_iterator() {};

			T* base() const { return (ptr); }
			T& operator*() const { return (*ptr); }
			random_access_iterator& operator++() { ++ptr; return (*this); }
			random_access_iterator operator++(int) { random_access_iterator tmp(*this); ++ptr; return (tmp); }
			random_access_iterator& operator--() { --ptr; return (*this); }
			random_access_iterator operator--(int) { random_access_iterator tmp(*this); --ptr; return (tmp); }
			random_access_iterator& operator+=(difference_type n) { ptr += n; return (*this); }
			random_access_iterator& operator-=(difference_type n) { ptr -= n; return (*this); }
			T& operator[](long n) const { return (ptr[n]); }
			bool operator!() const { return (!ptr); }
			operator random_access_iterator<const T>() { return random_access_iterator<const T>(ptr); }
	};

	template <class Iterator>
	random_access_iterator<Iterator>
	operator+(const random_access_iterator<Iterator>& lhs, typename random_access_iterator<Iterator>::difference_type n) {
		return random_access_iterator<Iterator>(lhs.base() + n); }

	template <class Iterator>
	random_access_iterator<Iterator>
	operator-(const random_access_iterator<Iterator>& lhs, typename random_access_iterator<Iterator>::difference_type n) {
		return random_access_iterator<Iterator>(lhs.base() - n); }

	template <class Iterator>
	random_access_iterator<Iterator>
	operator+(typename random_access_iterator<Iterator>::difference_type n, const random_access_iterator<Iterator>& rhs) {
		return random_access_iterator<Iterator>(rhs.base() + n); }

	template <class Iterator>
	random_access_iterator<Iterator>
	operator-(typename random_access_iterator<Iterator>::difference_type n, const random_access_iterator<Iterator>& rhs) {
		return random_access_iterator<Iterator>(rhs.base() - n); }

	template <typename Iterator1, typename Iterator2>
	typename random_access_iterator<Iterator1>::difference_type
	operator+(random_access_iterator<Iterator1> const & lhs, random_access_iterator<Iterator2> const & rhs) {
		return (lhs.base() + rhs.base()); }

	template <typename Iterator1, typename Iterator2>
	typename random_access_iterator<Iterator1>::difference_type
	operator-(random_access_iterator<Iterator1> const & lhs, random_access_iterator<Iterator2> const & rhs) {
		return (lhs.base() - rhs.base()); }

	template <typename Iterator1, typename Iterator2>
	bool operator==(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) {
		return (lhs.base() == rhs.base()); }

	template <typename Iterator1, typename Iterator2>
	bool operator!=(random_access_iterator<Iterator1> const & lhs, random_access_iterator<Iterator2> const & rhs) {
		return (lhs.base() != rhs.base()); }

	template <typename Iterator1, typename Iterator2>
	bool operator<(random_access_iterator<Iterator1> const & lhs, random_access_iterator<Iterator2> const & rhs) {
		return (lhs.base() < rhs.base()); }

	template <typename Iterator1, typename Iterator2>
	bool operator<=(random_access_iterator<Iterator1> const & lhs, random_access_iterator<Iterator2> const & rhs) {
		return (lhs.base() <= rhs.base()); }

	template <typename Iterator1, typename Iterator2>
	bool operator>(random_access_iterator<Iterator1> const & lhs, random_access_iterator<Iterator2> const & rhs) {
		return (lhs.base() > rhs.base()); }

	template <typename Iterator1, typename Iterator2>
	bool operator>=(random_access_iterator<Iterator1> const & lhs, random_access_iterator<Iterator2> const & rhs) {
		return (lhs.base() >= rhs.base()); }

	template <typename T, typename N>
	class bidirectional_iterator : public iterator<bidirectional_iterator_tag, T>
	{
		private:
			N* node;
		public:
			typedef iterator<bidirectional_iterator_tag, T> iterator_type;
			typedef typename iterator_traits<bidirectional_iterator>::value_type		value_type;
			typedef typename iterator_traits<bidirectional_iterator>::difference_type	difference_type;
			typedef typename iterator_traits<bidirectional_iterator>::pointer			pointer;
			typedef typename iterator_traits<bidirectional_iterator>::reference			reference;
			typedef typename iterator_traits<bidirectional_iterator>::iterator_category	iterator_category;

			bidirectional_iterator() : node(NULL) {}
			bidirectional_iterator(N* node) : node(node) {}
			bidirectional_iterator(const bidirectional_iterator& src) : node(src.node) {}
			bidirectional_iterator& operator=(const bidirectional_iterator& src) { node = src.node; return (*this); }
			~bidirectional_iterator() {};

			N* base() const { return (node); }
			T& operator*() const
			{
				if (!node)
					throw std::exception();
				return (*(node->val));
			}
			T* operator->() const
			{
				if (!node)
					throw std::exception();
				return (node->val);
			}
			bidirectional_iterator& operator++()
			{
				if (!node)
					throw std::exception();
				if (node->right)
				{
					node = node->right;
					while (node && node->left)
						node = node->left;
					return (*this);
				}
				N* parent = node->par;
				while (parent && parent->left != node)
				{
					node = parent;
					parent = parent->par;
				}
				node = parent;
				return (*this);
			}
			bidirectional_iterator operator++(int)
			{
				bidirectional_iterator tmp = *this;
				*this = operator++();
				return (tmp);
			}
			bidirectional_iterator& operator--()
			{
				if (!node)
					throw std::exception();
				if (node->left)
				{
					node = node->left;
					while (node && node->right)
						node = node->right;
					return (*this);
				}
				N* parent = node->par;
				while (parent && parent->right != node)
				{
					node = parent;
					parent = parent->par;
				}
				node = parent;
				return (*this);
			}
			bidirectional_iterator operator--(int)
			{
				bidirectional_iterator tmp = *this;
				*this = operator--();
				return (tmp);
			}
			bool operator==(const bidirectional_iterator& src) const { return (node == src.node); }
			bool operator!=(const bidirectional_iterator& src) const { return (node != src.node); }
			operator bidirectional_iterator<const T, N>() { return bidirectional_iterator<const T, N>(node); }
	};

	template <class Iterator, class N>
	bidirectional_iterator<Iterator, N>
	operator+(const bidirectional_iterator<Iterator, N>& lhs, typename bidirectional_iterator<Iterator, N>::difference_type n) {
		return bidirectional_iterator<Iterator, N>(lhs.base() + n); }

	template <class Iterator, class N>
	bidirectional_iterator<Iterator, N>
	operator-(const bidirectional_iterator<Iterator, N>& lhs, typename bidirectional_iterator<Iterator, N>::difference_type n) {
		return bidirectional_iterator<Iterator, N>(lhs.base() - n); }

	template <class Iterator, class N>
	bidirectional_iterator<Iterator, N>
	operator+(typename bidirectional_iterator<Iterator, N>::difference_type n, const bidirectional_iterator<Iterator, N>& rhs) {
		return bidirectional_iterator<Iterator, N>(rhs.base() + n); }

	template <class Iterator, class N>
	bidirectional_iterator<Iterator, N>
	operator-(typename bidirectional_iterator<Iterator, N>::difference_type n, const bidirectional_iterator<Iterator, N>& rhs) {
		return bidirectional_iterator<Iterator, N>(rhs.base() - n); }

	template <typename Iterator1, typename Iterator2, typename N>
	typename bidirectional_iterator<Iterator1, N>::difference_type
	operator+(bidirectional_iterator<Iterator1, N> const & lhs, bidirectional_iterator<Iterator2, N> const & rhs) {
		return (lhs.base() + rhs.base()); }

	template <typename Iterator1, typename Iterator2, typename N>
	typename bidirectional_iterator<Iterator1, N>::difference_type
	operator-(bidirectional_iterator<Iterator1, N> const & lhs, bidirectional_iterator<Iterator2, N> const & rhs) {
		return (lhs.base() - rhs.base()); }

	template <typename Iterator1, typename Iterator2, typename N>
	bool operator==(const bidirectional_iterator<Iterator1, N>& lhs, const bidirectional_iterator<Iterator2, N>& rhs) {
		return (lhs.base() == rhs.base()); }

	template <typename Iterator1, typename Iterator2, typename N>
	bool operator!=(bidirectional_iterator<Iterator1, N> const & lhs, bidirectional_iterator<Iterator2, N> const & rhs) {
		return (lhs.base() != rhs.base()); }

	template <typename Iterator1, typename Iterator2, typename N>
	bool operator<(bidirectional_iterator<Iterator1, N> const & lhs, bidirectional_iterator<Iterator2, N> const & rhs) {
		return (lhs.base() < rhs.base()); }

	template <typename Iterator1, typename Iterator2, typename N>
	bool operator<=(bidirectional_iterator<Iterator1, N> const & lhs, bidirectional_iterator<Iterator2, N> const & rhs) {
		return (lhs.base() <= rhs.base()); }

	template <typename Iterator1, typename Iterator2, typename N>
	bool operator>(bidirectional_iterator<Iterator1, N> const & lhs, bidirectional_iterator<Iterator2, N> const & rhs) {
		return (lhs.base() > rhs.base()); }

	template <typename Iterator1, typename Iterator2, typename N>
	bool operator>=(bidirectional_iterator<Iterator1, N> const & lhs, bidirectional_iterator<Iterator2, N> const & rhs) {
		return (lhs.base() >= rhs.base()); }
}

#endif
