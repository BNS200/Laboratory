#include <iostream>
#include <cmath>
#include <stdexcept>
#include "array.h"
#include <numeric>


Array::Array(int size){
    m_size = size;
    m_array = new int[m_size];
    if (size < 0){
        size = -size;   
    }     
    for (int i = 0; i < 0; ++i){
        m_array[i] = 0;
    }
}

Array::Array(const Array& other){
    m_size = other.m_size;
    m_array = new int[m_size];
    for (int i = 0; i < m_size; ++i){
        m_array[i] = other.m_array[i];
    }
}

Array::~Array(){
    delete[] m_array;
}

Array::Array(Array&& other){
    m_size = other.m_size;
    m_array = other.m_array;
    other.m_array = nullptr;
}

bool Array::insert(const int index,const int& value){
    if (index < 0 || index > m_size)
    return false;

    int* newArray = new int[m_size + 1];
    for(int i = 0; i < index; ++i){
        newArray[i] = m_array[i];
    }

    newArray[index] = value;

    for (int i = index + 1;i < m_size; ++i){
        newArray[i] = m_array[i-1];
    }

    delete[] m_array;
    m_array = newArray;
    m_size++;

    return true;
}

int Array::getSize(){
    return m_size;
}

int Array::findFirstOccurence(int value){
    for (int i = 0;i < m_size; ++i){
        if (m_array[i] = value){
        return i;
    } else{
        return -1;
        }
    }
}

bool Array::removeNumber(const int index){
    if (index < 0 || index > m_size){
        return false;
    }
    int* newArray = new int[m_size-1];
    for (int i = 0; i < index; ++i){
        newArray[i] = m_array[i];
    }
    for (int i = index; i < m_size - 1; ++i){
        newArray[i] = m_array[i + 1];
    }

    delete[] m_array;
    m_array = newArray;
    return true;
}

bool Array::removeAllNumbers(){
    
}

