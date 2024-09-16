#include <iostream>
#pragma once

class Fraction {
    public:
       void setNumerator(int numerator){
           this->numerator = numerator;
       }
       void setDenomenator(int denomenator){
           this->denomenator = denomenator;
       }
       int getNumerator(){
           return this->numerator;
       }
       int getDenomenator(){
           return this->denomenator;
       }
       Fraction(int numerator = 0,int denomenator = 1){
           setNumerator(numerator);
           setDenomenator(denomenator);
           if (denomenator == 0)
               throw std::invalid_argument("Значение знаменателя не может быть ноль");
       }

       private:
            int numerator;
            int denomenator;
};