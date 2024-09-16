#pragma once
#include <iostream>
#include <stdexcept>
class Fraction
{
private:
	int numerator;
	int denominator;

public:
	Fraction(int numerator = 0, int denominator = 1) {
		setNumerator(numerator);
		setDenominator(denominator);
	}
	int getNumerator() {
		return this->numerator;
	}
	int getDenominator() {
		return this->denominator;
	}
	void setNumerator(int numerator) {
		this->numerator = numerator;
	}
	void setDenominator(int denominator) {
		this->denominator = denominator;
	}

	Fraction operator+(Fraction b);
	Fraction operator-(Fraction b);
	Fraction operator*(Fraction b);
	Fraction operator/(Fraction b);
	bool operator<(Fraction b);
	bool operator>(Fraction b);
	bool operator==(Fraction b);
	bool operator!=(Fraction b);
};
