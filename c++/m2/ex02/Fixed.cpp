#include "Fixed.hpp"

Fixed::Fixed()
{
	this->value = 0;
}

Fixed::Fixed(const int val)
{
	this->value = val << bits;
}

Fixed::Fixed(const float val)
{
	this->value = (int)roundf(val * (1 << bits));
}

Fixed::Fixed(const Fixed &src)
{
	*this = src;
}

Fixed &Fixed::operator=(const Fixed &right)
{
	if (this != &right)
		this->value = right.getRawBits();
	return (*this);
}

Fixed::~Fixed() {}

int	Fixed::getRawBits() const
{
	return (this->value);
}

void Fixed::setRawBits(int const raw)
{
	this->value = raw;
}

int Fixed::toInt(void) const
{
	return (this->value >> bits);
}

float Fixed::toFloat(void) const
{
	return ((float)this->value / (1 << bits));
}

std::ostream &operator<<(std::ostream &dst, const Fixed &src)
{
	dst << src.toFloat();
	return (dst);
}

bool Fixed::operator>(Fixed &right)
{
	if (this->value > right.value)
		return (true);
	return (false);
}

bool Fixed::operator<(Fixed &right)
{
	if (this->value < right.value)
		return (true);
	return (false);
}

bool Fixed::operator>=(Fixed &right)
{
	if (this->value >= right.value)
		return (true);
	return (false);
}

bool Fixed::operator<=(Fixed &right)
{
	if (this->value <= right.value)
		return (true);
	return (false);
}

bool Fixed::operator==(Fixed &right)
{
	if (this->value == right.value)
		return (true);
	return (false);
}

bool Fixed::operator!=(Fixed &right)
{
	if (this->value != right.value)
		return (true);
	return (false);
}

Fixed Fixed::operator+(Fixed right)
{
	Fixed tmp;
	tmp.value = this->value + right.value;
	return (tmp);
}

Fixed Fixed::operator-(Fixed right)
{
	Fixed tmp;
	tmp.value = this->value - right.value;
	return (tmp);
}

Fixed Fixed::operator*(Fixed right)
{
	Fixed tmp;
	tmp.value = this->value * right.value / (1 << bits);
	return (tmp);
}

Fixed Fixed::operator/(Fixed right)
{
	Fixed tmp;
	tmp.value = this->value * (1 << bits) / right.value;
	return (tmp);
}

Fixed &Fixed::operator++()
{
	this->value++;
	return (*this);
}

Fixed Fixed::operator++(int)
{
	Fixed tmp = *this;
	++*this;
	return (tmp);
}

Fixed &Fixed::operator--()
{
	this->value--;
	return (*this);
}

Fixed Fixed::operator--(int)
{
	Fixed tmp = *this;
	--*this;
	return (tmp);
}

Fixed &Fixed::min(Fixed &first, Fixed &second)
{
	if (first.value < second.value)
		return (first);
	return (second);
}

Fixed Fixed::min(const Fixed &first, const Fixed &second)
{
	Fixed tmp;
	if (first.value < second.value)
		tmp.value = first.value;
	else
		tmp.value = second.value;
	return (tmp);
}

Fixed &Fixed::max(Fixed &first, Fixed &second)
{
	if (first.value > second.value)
		return (first);
	return (second);
}

Fixed Fixed::max(const Fixed &first, const Fixed &second)
{
	Fixed tmp;
	if (first.value > second.value)
		tmp.value = first.value;
	else
		tmp.value = second.value;
	return (tmp);
}
