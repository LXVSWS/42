#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>

template<typename T>
class Array
{
	T *array;
	unsigned int size;

	public:
		Array()
		{
			this->array = new T[0];
			this->size = 0;
		}
		Array(unsigned int n)
		{
			this->array = new T[n];
			for (unsigned int i = 0 ; i < n ; i++)
				this->array[i] = 0;
			this->size = n;
		}
		Array(const Array &src)
		{
			this->array = new T[src.size];
			for (unsigned int i = 0 ; i < src.size ; i++)
				this->array[i] = src.array[i];
			this->size = src.size;
		}
		Array & operator=(const Array &src)
		{
			if (this != &src)
			{
				delete[] this->array;
				this->array = new T[src.size];
				for (unsigned int i = 0 ; i < src.size ; i++)
					this->array[i] = src.array[i];
				this->size = src.size;
			}
			return (*this);
		}
		T & operator[](unsigned int i)
		{
			if (!this->size || i > this->size - 1)
				throw std::exception();
			else
				return (this->array[i]);
		}
		~Array()
		{
			delete[] this->array;
		}
};

#endif
