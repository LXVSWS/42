#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed
{
	int	value;
	static const int bits = 8;

public:
	Fixed();
	Fixed(const int val);
	Fixed(const float val);
	Fixed(const Fixed &src);
	Fixed &operator=(const Fixed &right);
	~Fixed();

	int	getRawBits(void) const;
	void setRawBits(int const raw);
	float toFloat(void) const;
	int toInt(void) const;

	bool operator>(Fixed &right);
	bool operator<(Fixed &right);
	bool operator>=(Fixed &right);
	bool operator<=(Fixed &right);
	bool operator==(Fixed &right);
	bool operator!=(Fixed &right);

	Fixed operator+(Fixed right);
	Fixed operator-(Fixed right);
	Fixed operator*(Fixed right);
	Fixed operator/(Fixed right);

	Fixed &operator++();
	Fixed operator++(int);
	Fixed &operator--();
	Fixed operator--(int);

	static Fixed &min(Fixed &first, Fixed &second);
	static Fixed min(const Fixed &first, const Fixed &second);
	static Fixed &max(Fixed &first, Fixed &second);
	static Fixed max(const Fixed &first, const Fixed &second);
};

std::ostream &operator<<(std::ostream &dst, const Fixed &src);

#endif
