#ifndef ITERATOR_HPP
#define ITERATOR_HPP

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

			T& operator*() const { return (*ptr); }
			random_access_iterator& operator++() { ++ptr; return (*this); }
			random_access_iterator operator++(int) { random_access_iterator tmp(*this); ++ptr; return (tmp); }
			random_access_iterator& operator--() { --ptr; return (*this); }
			random_access_iterator operator--(int) { random_access_iterator tmp(*this); --ptr; return (tmp); }
			random_access_iterator operator+(const T& n) const { return (random_access_iterator(ptr + n)); }
			random_access_iterator& operator+=(const T& n) { ptr += n; return (*this); }
			random_access_iterator operator-(const T& n) const { return (random_access_iterator(ptr - n)); }
			random_access_iterator& operator-=(const T& n) { ptr -= n; return (*this); }
			bool operator==(const random_access_iterator& src) const { return (ptr == src.ptr); }
			bool operator!=(const random_access_iterator& src) const { return (ptr != src.ptr); }
			bool operator<(const random_access_iterator& src) const { return (ptr < src.ptr); }
			bool operator<=(const random_access_iterator& src) const { return (ptr <= src.ptr); }
			bool operator>(const random_access_iterator& src) const { return (ptr > src.ptr); }
			bool operator>=(const random_access_iterator& src) const { return (ptr >= src.ptr); }
			T& operator[](long n) const { return (ptr[n]); }
			operator random_access_iterator<const T>() { return random_access_iterator<const T>(ptr); }
	};

	template <typename T, typename N>
	class bidirectional_iterator : public iterator<bidirectional_iterator_tag, T>
	{
		private:
			N* node;
			N* prev;
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

			T& operator*() const { return (node->val); }
			T* operator->() const {
				std::cout << "\n" << node << "\nparent: " << node->par << "\nleft: " << node->left << "\nright: " << node->right << std::endl; return (node->val); }
			bidirectional_iterator& operator++()
			{
				if (node->right)
				{
					node = node->right;
					if (node->left)
						prev = node;
					while (node && node->left)
						node = node->left;
				}
				else if (node->par)
				{
					N* tmp = node;
					node = node->par;
					while (node && node->left != tmp)
						node = node->left;
				}
				if (!node && prev)
				{
					node = prev;
					prev = NULL;
				}
				if (!node && !prev)
					throw std::exception();
				return (*this);
			}
			bool operator!=(const bidirectional_iterator& src) const { return (node != src.node); }
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
			reverse_iterator(const reverse_iterator<Iter>& rev_it) { this->current = rev_it.current; }

			Iterator base() const { return (current); }
			reference operator*() const { Iterator tmp(current); --tmp; return (*tmp); }
			reverse_iterator& operator++() { --current; return (*this); }
			reverse_iterator operator++(int) { reverse_iterator tmp(*this); --current; return (tmp); }
			reverse_iterator& operator--() { ++current; return (*this); }
			reverse_iterator operator--(int) { reverse_iterator tmp(*this); ++current; return (tmp); }
			reverse_iterator operator+(const value_type& n) const { return (reverse_iterator(current - n)); }
			reverse_iterator& operator+=(const value_type& n) { current -= n; return (*this); }
			reverse_iterator operator-(const value_type& n) const { return (reverse_iterator(current + n)); }
			reverse_iterator& operator-=(const value_type& n) { current += n; return (*this); }
			pointer operator->() const { return &(operator*()); }
			reference operator[] (difference_type n) const { return (current[-n-1]); }
	};

	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator>& left, const reverse_iterator<Iterator>& right) {
		return (left.base() == right.base()); }

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& left, const reverse_iterator<Iterator>& right) {
		return (left.base() != right.base()); }

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator>& left, const reverse_iterator<Iterator>& right) {
		return (left.base() > right.base()); }

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& left, const reverse_iterator<Iterator>& right) {
		return (left.base() >= right.base()); }

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& left, const reverse_iterator<Iterator>& right) {
		return (left.base() < right.base()); }

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& left, const reverse_iterator<Iterator>& right) {
		return (left.base() <= right.base()); }

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, \
	const reverse_iterator<Iterator>& rev_it) {
		return (rev_it + n); }

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& left, \
	const reverse_iterator<Iterator>& right)
	{
		typename reverse_iterator<Iterator>::difference_type i = 0;
		for (Iterator it = right.base() ; it != left.base() ; ++it)
		{
			if (!*it)
				break;
			i++;
		}
		return (i);
	}
}

#endif
