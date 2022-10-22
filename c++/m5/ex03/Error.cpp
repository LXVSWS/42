#include "Error.hpp"

Error::Error(std::string param) : message(param) {}

Error::~Error() throw() {}

const char *Error::what() const throw()
{
	return (this->message.c_str());
}
