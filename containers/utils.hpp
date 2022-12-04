#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{
	template <bool Cond, class T = void>
	class enable_if
	{
	};

	template <class T>
	class is_integral
	{
	};

	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2);

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred);

	template <typename T1, typename T2>
	class pair
	{
		public:
			typedef T1 first_type;
			typedef T2 second_type;

			first_type first;
			second_type second;

			pair() {}
	};

	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		pair<T1, T2> p;
		p.first = x;
		p.second = y;
		return (p);
	}
}

#endif
