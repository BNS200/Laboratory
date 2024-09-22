#pragma once
#include <iostream>
#include <stdexcept>

class Fraction
{
private:
	int numerator;
	int denominator;

public:
	Fraction(const int numerator = 0, const int denominator = 1)
	{
		setNumerator(numerator);
		setDenominator(denominator);
	}

	inline int getNumerator() const noexcept
	{
		return this->numerator;
	}

	inline int getDenominator() const noexcept
	{
		return this->denominator;
	}

	inline void setNumerator(const int numerator) noexcept
	{
		this->numerator = numerator;
    }

    inline void setDenominator(const int denominator)
	{
		if (denominator == 0)
            throw std::invalid_argument("Знаменатель не может быть нулем.");

		this->denominator = denominator;
	}

	Fraction& operator+(const Fraction& fraction);
	Fraction& operator-(const Fraction& fraction);
	Fraction& operator*(const Fraction& fraction);
	Fraction& operator/(const Fraction& fraction);

	bool operator<(const Fraction& fraction) const;
	bool operator>(const Fraction& fraction) const;
	bool operator==(const Fraction& fraction) const;
	bool operator!=(const Fraction& fraction) const;

	void OutputFraction() const;
	Fraction InputFraction();
};
