#include <iostream>
#include "Fraction.h"

int main() {
    Fraction fraction(5, 9);
    fraction.outputFraction();

    Fraction inputFraction;
    inputFraction.inputFraction();
    inputFraction.outputFraction();

    return 0;
}