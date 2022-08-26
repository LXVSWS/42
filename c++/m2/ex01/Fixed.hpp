#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed
{
	int	value;
	static const int bits = 8;

public:
	Fixed();
	Fixed(const int val);
	Fixed(const float val);
	Fixed(const Fixed &src);
	Fixed &operator=(const Fixed &src);
	~Fixed();

	int	getRawBits(void) const;
	void setRawBits(int const raw);
	float toFloat(void) const;
	int toInt(void) const;
};

std::ostream &operator<<(std::ostream &dst, const Fixed &src);

#endif
