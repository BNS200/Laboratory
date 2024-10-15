#pragma once
#include <iostream>
#include <numeric>
#include <cmath>
#include <stdexcept>

class Fraction
{
private:
	int numerator;
	int denominator;

public:
  Fraction (const int numerator = 0, const int denominator = 1);
  
  inline int getNumerator () noexcept;
  inline int getDenominator () noexcept;
  inline void setNumerator (const int numerator) noexcept;
  inline void setDenominator (const int denominator);

  Fraction &operator+ (const Fraction &fraction);
  Fraction &operator- (const Fraction &fraction);
  Fraction &operator* (const Fraction &fraction);
  Fraction &operator/ (const Fraction &fraction);
  Fraction pow (int exponent);
  Fraction sqrt ();

  bool operator< (const Fraction &fraction) const;
  bool operator> (const Fraction &fraction) const;
  bool operator== (const Fraction &fraction) const;
  bool operator!= (const Fraction &fraction) const;

  Fraction inputFraction ();
  void outputFraction () const;
  void reducibleFraction ();
};
