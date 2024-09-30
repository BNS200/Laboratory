#include <iostream>
#include "Fraction.h"

int main() {
    Fraction fraction(5, 9);
    fraction.OutputFraction();

    Fraction inputFraction;
    inputFraction.InputFraction();
    inputFraction.OutputFraction();

    return 0;
}