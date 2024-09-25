#include <gtest/gtest.h>
#include "Fraction.h"


TEST(Fraction, Constructor) {
  Fraction f1(1, 2);
  Fraction f2;
  f2.setNumerator(1);
  f2.setDenominator(2);
  EXPECT_EQ(f1, f2);
}

TEST(Fraction, Addition) {
  Fraction f1(-1, 2);
  Fraction f2(-2, -4);
  Fraction f3(0, 1);
  EXPECT_EQ(f1 + f2, f3);
}

TEST(Fraction, Subtraction) {
  Fraction f1(-1, 2);
  Fraction f2(-2, 4);
  Fraction f3(0, 1);
  EXPECT_EQ(f1 - f2, f3);
}

TEST(Fraction, Multiplication) {
  Fraction f1(-1, 2);
  Fraction f2(0, 4);
  Fraction f3(0, 1);
  EXPECT_EQ(f1 * f2, f3);
}

TEST(Fraction, Division) {
  Fraction f1(1, 2);
  Fraction f2(2, 4);
  Fraction f3(1, 1);
  EXPECT_EQ(f1 / f2, f3);
}

TEST(Fraction, LessThan) {
  Fraction f1(1, 2);
  Fraction f2(5, 100);
  EXPECT_TRUE(f2 < f1 );
}

TEST(Fraction, GreaterThan) {
  Fraction f1(1, 2);
  Fraction f2(2, 3);
  EXPECT_TRUE(f2 > f1 );
}

TEST(Fraction, PowFraction){
  Fraction frac(2, 3);
  Fraction result = frac.pow(3);
  EXPECT_EQ(result.getNumerator(), 8);
  EXPECT_EQ(result.getDenominator(), 27);
}

TEST(Fraction, SQRT){
  Fraction frac(16, 25);
  Fraction frac2(4, 5);
  EXPECT_EQ(frac.sqrt(),frac2);
}

TEST(Fraction, Equals){
  Fraction f1(1, 4);
  Fraction f2(25, 100);
  EXPECT_TRUE(f1 == f2);
}

TEST(Fraction, NoEquals){
  Fraction f1(2, 4);
  Fraction f2(25, 100);
  EXPECT_FALSE(f1 == f2);
}