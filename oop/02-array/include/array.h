#pragma once
#include <iostream>

class Array{
public:
    Array(int size);
    ~Array();
    Array(const Array& other);
    Array(Array&& other);
    void outputArray() const;
    Array inputArray();
    int getSize();
    bool insert(const int index,const int& value);
    int findFirstOccurence(int value);
    bool removeNumber(const int index);
    bool removeAllNumbers();


private:
    int* m_array = nullptr;
    int m_size = 0; 
    
};
