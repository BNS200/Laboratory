#include <iostream>
#include <cmath>
#include <stdexcept>
#include "Fraction.h"
#include <numeric>

Fraction::Fraction(const int numerator = 0, const int denominator = 1)
{
	setNumerator(numerator);
	setDenominator(denominator);
	reducibleFraction();
}

int Fraction::getDenominator()
{
	return this->denominator;
}

int Fraction::getNumerator()
{
	return this->numerator;
}

void Fraction::setNumerator(const int numerator)
{
	this->numerator = numerator;
}

void Fraction::setDenominator (const int denominator)
{
    if (denominator == 0)
        throw std::invalid_argument("The denominator cannot be 0");

    this->denominator = denominator;
}
	
Fraction& Fraction::operator+(const Fraction& fraction)
{
    this->setNumerator(this->numerator * fraction.denominator + this->denominator * fraction.numerator);
    this->setDenominator(this->denominator * fraction.denominator);
    reducibleFraction();
    return *this;
}

Fraction& Fraction::operator-(const Fraction& fraction)
{
    this->setNumerator(this->numerator * fraction.denominator - this->denominator * fraction.numerator);
    this->setDenominator(this->denominator * fraction.denominator);
    reducibleFraction();
    return *this;
    
}

Fraction& Fraction::operator*(const Fraction& fraction)
{
    this->setNumerator(this->numerator * fraction.numerator);
    this->setDenominator(this->denominator * fraction.denominator);
    reducibleFraction();
    return *this;
    
}

Fraction& Fraction::operator/(const Fraction& fraction)
{ 
    this->setNumerator(this->numerator * fraction.denominator);
    this->setDenominator(this->denominator * fraction.numerator);
    reducibleFraction();
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

void Fraction::outputFraction() const
{
    std::cout << numerator << "/" << denominator << std::endl;
}

Fraction Fraction::inputFraction()
{
	std::cin >> numerator;
	std::cout << "/";
	std::cin >> denominator;
    return Fraction(numerator, denominator);
}

void Fraction::reducibleFraction()
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
            throw std::invalid_argument("The number cannot be negative");
        }
        return Fraction(static_cast<int>(std::sqrt(numerator)), static_cast<int>(std::sqrt(denominator)));
    }
