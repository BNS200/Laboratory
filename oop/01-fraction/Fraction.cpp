#include "Fraction.h"

Fraction& Fraction::operator+(const Fraction& fraction)
{
    this->setNumerator(this->numerator * fraction.denominator + this->denominator * fraction.numerator);
    this->setDenominator(this->denominator * fraction.denominator);
    IrreducibleFraction();
    return *this;
}

Fraction& Fraction::operator-(const Fraction& fraction)
{
    this->setNumerator(this->numerator * fraction.denominator - this->denominator * fraction.numerator);
    this->setDenominator(this->denominator * fraction.denominator);
    IrreducibleFraction();
    return *this;
    
}

Fraction& Fraction::operator*(const Fraction& fraction)
{
    this->setNumerator(this->numerator * fraction.numerator);
    this->setDenominator(this->denominator * fraction.denominator);
    IrreducibleFraction();
    return *this;
    
}

Fraction& Fraction::operator/(const Fraction& fraction)
{ 
    this->setNumerator(this->numerator * fraction.denominator);
    this->setDenominator(this->denominator * fraction.numerator);
    IrreducibleFraction();
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

void Fraction::IrreducibleFraction()
{
    int gcd = std::gcd(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
    if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
}
}

Fraction Fraction::pow(int exponent){
    return Fraction(static_cast<int>(std::pow(numerator, exponent)), static_cast<int>(std::pow(denominator, exponent)));
}

Fraction Fraction::sqrt(){
        if (numerator < 0 || denominator < 0) {
            throw std::invalid_argument("Число не может быть отрицательным");
        }
        return Fraction(static_cast<int>(std::sqrt(numerator)), static_cast<int>(std::sqrt(denominator)));
    }