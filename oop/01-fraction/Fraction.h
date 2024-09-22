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
		if (denominator == 0) {
            throw std::invalid_argument("Знаменатель не может быть нулем.");
        }
	}
	inline int getNumerator()  const {
		return this->numerator;
	}
	inline int getDenominator() const {
		return this->denominator;
	}
	inline void setNumerator(int numerator) {
		this->numerator = numerator;
    }
    inline void setDenominator(int denominator){
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


	void OutputFraction();
	Fraction InputFraction();

};
