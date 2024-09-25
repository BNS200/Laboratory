#include <iostream>
#include "Fraction.h"

int main() {
    Fraction fraction(3, 4);
    fraction.OutputFraction();

    Fraction inputFraction;
    inputFraction.InputFraction();
    inputFraction.OutputFraction();

    return 0;
}