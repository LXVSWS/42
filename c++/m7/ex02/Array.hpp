#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>

template<typename T>
class Array
{
	T *array;

	public:
		Array()
		{
			this->array = new T[0];
		}
		Array(unsigned int n)
		{
			this->array = new T[n];
			for (unsigned int i = 0 ; i < n ; i++)
				this->array[i] = 0;
		}
		Array(const Array &src)
		{
			unsigned int size = 0;
			if (src.array)
				while (src.array[size])
					size++;
			this->array = new T[size];
			for (unsigned int i = 0 ; i < size ; i++)
				this->array[i] = src.array[i];
		}
		Array & operator=(const Array &src)
		{
			if (this != &src)
			{
				delete[] this->array;
				unsigned int size = 0;
				if (src.array)
					while (src.array[size])
						size++;
				this->array = new T[size];
				for (unsigned int i = 0 ; i < size ; i++)
					this->array[i] = src.array[i];
			}
			return (*this);
		}
		T & operator[](unsigned int i)
		{
			try
			{
				if (!this->array[i])
					throw std::exception();
			}
			catch(const std::exception& e)
			{
				std::cerr << "Array::InvalidIndexException" << std::endl;
			}
			return (this->array[i]);
		}
		~Array()
		{
			delete[] this->array;
		}
};

#endif
