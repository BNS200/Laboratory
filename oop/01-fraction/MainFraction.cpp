#include <iostream>
#include "Fraction.h"

using std::cout;
using std::endl;


int main() {
    Fraction fraction1(5, 9);
    fraction1.outputFraction();
    Fraction fraction2(9, 10);

    fraction2 = fraction1;
    fraction2.outputFraction();
    Fraction fraction3(fraction2);
    fraction3.outputFraction();
    Fraction fraction4(Fraction(1, 5));
    fraction4.outputFraction();
    bool greater = Fraction(1, 3) > Fraction(1, 2);
    bool less = Fraction(1, 3).operator<(Fraction(1, 2));
    cout << static_cast<int>(greater)  << " " << static_cast<int>(less)<< endl;
    return 0;
}