#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <vector>

class Span
{
	unsigned int N;
	std::vector<int> vector;

	public:
		Span();
		Span(unsigned int num);
		Span(const Span & src);
		Span & operator=(const Span & src);
		~Span();

		void addNumber(int num);
		unsigned int shortestSpan(void);
		unsigned int longestSpan(void);

		void addMultipleNumbers(int *nums, unsigned int size);
		void getNumbers(void);
};

#endif
