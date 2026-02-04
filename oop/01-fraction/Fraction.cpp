#include <iostream>
#include <cmath>
#include <stdexcept>
#include "Fraction.h"
#include <numeric>

Fraction::Fraction(const int numerator, const int denominator)
{
	setNumerator(numerator);
	setDenominator(denominator);
	reducibleFraction();
}
Fraction::Fraction(const Fraction& other){
	this->denominator = other.denominator;
	this->numerator = other.numerator; 
}

Fraction::Fraction(Fraction&& other){
	this->denominator = std::move(other.denominator);
	this->numerator = std::move(other.numerator);
	other.denominator = 0;
	other.numerator = 0;
}

Fraction& Fraction::operator=(const Fraction& other){
	if (this != &other){
			this->denominator = other.denominator;
			this->numerator = other.numerator;
	}

	return *this;
}

void swap(int& a, int& b)
{
	int c;
	c = a;
	a = b;
	b = c;
}

int Fraction::getDenominator() noexcept
{
	return this->denominator;
}

int Fraction::getNumerator() noexcept
{
	return this->numerator;
}

void Fraction::setNumerator(const int numerator) noexcept
{
	this->numerator = numerator;
}

void Fraction::setDenominator (const int denominator)
{
    if (denominator == 0)
        throw std::invalid_argument("The denominator cannot be 0");

    this->denominator = denominator;
}
	
Fraction Fraction::operator+(Fraction const b) const
{
	Fraction a;
	a.setNumerator(numerator * b.denominator + denominator * b.numerator);
	a.setDenominator(denominator * b.denominator);
	return a;
}
Fraction Fraction::operator-(Fraction const b) const
{
	Fraction a;
	a.setNumerator(numerator * b.denominator - denominator * b.numerator);
	a.setDenominator(denominator * b.denominator);
	return a;
}
Fraction Fraction::operator*(Fraction const b) const
{
	Fraction a;
	a.setNumerator(numerator * b.numerator);
	a.setDenominator(denominator * b.denominator);
	return a;
}
Fraction Fraction::operator/(Fraction const b) const
{
	Fraction a;
	a.setNumerator(numerator * b.denominator);
	a.setDenominator(denominator * b.numerator);
	return a;
}

bool Fraction::operator<(const Fraction& fraction) const
{
	return this->numerator / this->denominator < fraction.numerator / fraction.denominator;
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

void Fraction::inputFraction()
{
	std::cin >> numerator;
	std::cout << "/";
	std::cin >> denominator;
    
    if (denominator == 0)
	{
		std::cout << "Denominator cannot be 0"<< std::endl;
		numerator = 0;
		denominator = 1;
	}
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
    Fraction a;
	if (exponent < 0)
	{
		swap(numerator, denominator);
		exponent = -exponent;
	}
	for (int i = 0; i < exponent; i++)
	{
		a.setNumerator(a.numerator * numerator);
		a.setDenominator(a.denominator * denominator);
	}
	return a;
}

Fraction Fraction::sqrt(){
        if (numerator < 0 || denominator < 0) {
            throw std::invalid_argument("The number cannot be negative");
        }
        return Fraction(static_cast<int>(std::sqrt(numerator)), static_cast<int>(std::sqrt(denominator)));
}


