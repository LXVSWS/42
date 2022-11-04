#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>

template<typename T>
class Array
{
	T *array;
	unsigned int _size;

	public:
		Array()
		{
			this->array = new T[0];
			this->_size = 0;
		}
		Array(unsigned int n)
		{
			this->array = new T[n];
			for (unsigned int i = 0 ; i < n ; i++)
				this->array[i] = 0;
			this->_size = n;
		}
		Array(const Array &src)
		{
			this->array = new T[src._size];
			for (unsigned int i = 0 ; i < src._size ; i++)
				this->array[i] = src.array[i];
			this->_size = src._size;
		}
		Array & operator=(const Array &src)
		{
			if (this != &src)
			{
				delete[] this->array;
				this->array = new T[src._size];
				for (unsigned int i = 0 ; i < src._size ; i++)
					this->array[i] = src.array[i];
				this->_size = src._size;
			}
			return (*this);
		}
		T & operator[](unsigned int i)
		{
			if (!this->_size || i > this->_size - 1)
				throw std::exception();
			else
				return (this->array[i]);
		}
		~Array()
		{
			delete[] this->array;
		}

		unsigned int size()
		{
			return (this->_size);
		}
};

#endif
