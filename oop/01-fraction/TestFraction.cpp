#include <gtest/gtest.h>
#include "Fraction.h"

TEST(Fraction, Constructor) {
  Fraction f1(1, 2);
  Fraction f2;
  f2.setNumerator(1);
  f2.setDenominator(2);
  EXPECT_EQ(f1, f2);
}

TEST(Fraction, OperatorPlus) {
  Fraction f1(1, 2);
  Fraction f2(2, 4);
  Fraction f3(8, 8);
  EXPECT_EQ(f1 + f2, f3);
}
