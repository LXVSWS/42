#ifndef ERROR_HPP
#define ERROR_HPP

#include <iostream>

class Error : public std::exception
{
	std::string message;

	public:
		Error(std::string);
		~Error() throw();
		const char *what() const throw();
};

#endif
