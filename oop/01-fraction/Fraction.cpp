#include <iostream>
#include "Fraction.h"

Fraction Fraction::operator+(Fraction b)
{
    Fraction result;
    result.setDenominator(this->denominator * b.denominator);
    result.setNumerator(this->numerator * b.denominator + this->denominator * b.numerator);
    return result;
}

Fraction Fraction::operator-(Fraction b)
{
    Fraction result;
    result.setDenominator(this->denominator * denominator);
    result.setNumerator(this->numerator * b.denominator + this->denominator * b.numerator);
    return result;
}

Fraction Fraction::operator*(Fraction b)
{
    Fraction result;
    result.setDenominator(this->denominator * denominator);
    result.setNumerator(this->numerator * b.numerator);
    return result;
}

Fraction Fraction::operator/(Fraction b)
{ 
    Fraction result;
    result.setDenominator(this->denominator * b.numerator);
    result.setNumerator(this->numerator * b.denominator);
    return result;   
}


bool Fraction::operator<(Fraction b) {
	return (this->numerator * b.denominator < this->denominator * b.numerator);
}
bool Fraction::operator>(Fraction b) {
	return (this->numerator * b.denominator > this->denominator * b.numerator);
}
bool Fraction::operator==(Fraction b) {
	return (this->numerator * b.denominator == this->denominator * b.numerator);
}
bool Fraction::operator!=(Fraction b) {
	return (this->numerator * b.denominator != this->denominator * b.numerator);
}
