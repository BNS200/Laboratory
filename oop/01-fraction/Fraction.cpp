#include "Fraction.h"

Fraction& Fraction::operator+(const Fraction& fraction)
{
    this->setNumerator(this->numerator * fraction.denominator + this->denominator * fraction.numerator);
    this->setDenominator(this->denominator * fraction.denominator);
    return *this;
}

Fraction& Fraction::operator-(const Fraction& fraction)
{
    this->setNumerator(this->numerator * fraction.denominator - this->denominator * fraction.numerator);
    this->setDenominator(this->denominator * fraction.denominator);
    return *this;
}

Fraction& Fraction::operator*(const Fraction& fraction)
{
    this->setNumerator(this->numerator * fraction.numerator);
    this->setDenominator(this->denominator * fraction.denominator);
    return *this;
}

Fraction& Fraction::operator/(const Fraction& fraction)
{ 
    this->setNumerator(this->numerator * fraction.denominator);
    this->setDenominator(this->denominator * fraction.numerator);
    return *this;
}

bool Fraction::operator<(const Fraction& fraction) const
{
	return this->numerator / fraction.denominator < this->denominator / fraction.numerator;
}

bool Fraction::operator>(const Fraction& fraction) const
{
	return fraction < *this;
}

bool Fraction::operator==(const Fraction& fraction) const
{
	return this->numerator == fraction.numerator and this->denominator == fraction.denominator;
}

bool Fraction::operator!=(const Fraction& fraction) const
{
	return !(*this == fraction);
}

void Fraction::OutputFraction() const
{
    std::cout << numerator << "/" << denominator << std::endl;
}

Fraction Fraction::InputFraction()
{
	std::cin >> numerator;
	std::cout << "/";
	std::cin >> denominator;
    return Fraction(numerator, denominator);
}
