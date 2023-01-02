#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
			typedef T1 first_type;
			typedef T2 second_type;

			first_type first;
			second_type second;

			pair() : first(T1()), second(T2()) {}
			template<class U, class V>
			pair(const pair<U,V>& pr) : first(pr.first), second(pr.second) {}
			pair(const first_type& a, const second_type& b) : first(a), second(b) {}
			pair& operator=(const pair& pr) { first = pr.first; second = pr.second; return(*this); }
	};

	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y) { return(pair<T1,T2>(x,y)); }

	template <class T1, class T2>
	bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return (lhs.first == rhs.first && lhs.second == rhs.second); }

	template <class T1, class T2>
	bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs == rhs); }

	template <class T1, class T2>
	bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second)); }

	template <class T1, class T2>
	bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return (!(rhs < lhs)); }

	template <class T1, class T2>
	bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return (rhs < lhs); }

	template <class T1, class T2>
	bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return (!(lhs < rhs)); }

	template <bool, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <class T>
	class is_integral										:	public std::false_type {};
	template <> struct is_integral<bool> 					: 	public std::true_type {};
	template <> struct is_integral<char> 					: 	public std::true_type {};
	template <> struct is_integral<char16_t> 				: 	public std::true_type {};
	template <> struct is_integral<char32_t>				: 	public std::true_type {};
	template <> struct is_integral<wchar_t> 				: 	public std::true_type {};
	template <> struct is_integral<signed char> 			: 	public std::true_type {};
	template <> struct is_integral<short int> 				: 	public std::true_type {};
	template <> struct is_integral<int> 					: 	public std::true_type {};
	template <> struct is_integral<long int>				: 	public std::true_type {};
	template <> struct is_integral<long long int>			: 	public std::true_type {};
	template <> struct is_integral<unsigned char>			: 	public std::true_type {};
	template <> struct is_integral<unsigned short int>		: 	public std::true_type {};
	template <> struct is_integral<unsigned int>			: 	public std::true_type {};
	template <> struct is_integral<unsigned long int>		: 	public std::true_type {};
	template <> struct is_integral<unsigned long long int>	: 	public std::true_type {};

	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		for (; (first1 != last1) && (first2 != last2) ; ++first1, ++first2)
		{
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template<class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
	{
		for (; (first1 != last1) && (first2 != last2) ; ++first1, ++first2)
		{
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}
}

#endif
