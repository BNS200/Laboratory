#include <iostream>
#include <cmath>
#include <stdexcept>
#include <numeric>

//#include "array.h"

// template<typename T>
// Array<T>::Array(int size){
//     m_size = size;
//     m_array = new int[m_size];
//     if (size < 0){
//         size = -size;   
//     }     
//     for (int i = 0; i < 0; ++i){
//         m_array[i] = 0;
//     }
// }
// template<typename T>
// Array<T>::Array(const Array& other){
//     m_size = other.m_size;
//     m_array = new int[m_size];
//     for (int i = 0; i < m_size; ++i){
//         m_array[i] = other.m_array[i];
//     }
// }
// template<typename T>
// Array<T>::~Array(){
//     delete[] m_array;
// }

// template<typename T>
// Array<T>::Array(Array&& other){
//     m_size = other.m_size;
//     m_array = other.m_array;
//     other.m_array = nullptr;
// }

// template<typename T>
// bool Array<T>::insert(const T& index,const T& value){
//     if (index < 0 || index > m_size)
//     return false;

//     int* newArray = new int[m_size + 1];
//     for(int i = 0; i < index; ++i){
//         newArray[i] = m_array[i];
//     }

//     newArray[index] = value;

//     for (int i = index + 1;i < m_size; ++i){
//         newArray[i] = m_array[i-1];
//     }

//     delete[] m_array;
//     m_array = newArray;
//     m_size++;

//     return true;
// }

// template<typename T>
// int Array<T>::getSize() const noexcept{
//     return m_size;
// }

// template<typename T>
// int Array<T>::findFirstOccurence(const T& value) const{
//     for (int i = 0;i < m_size; ++i){
//         if (m_array[i] == value){
//         return i;
//     } else{
//         return -1;
//         }
//     }
// }

// template<typename T>
// bool Array<T>::removeByIndex(const T& index){
//     if (index < 0 || index > m_size){
//         return false;
//     }
//     int* newArray = new int[m_size-1];
//     for (int i = 0; i < index; ++i){
//         newArray[i] = m_array[i];
//     }
//     for (int i = index; i < m_size - 1; ++i){
//         newArray[i] = m_array[i + 1];
//     }

//     delete[] m_array;
//     m_array = newArray;
//     --m_size;
//     return true;
// }

// template<typename T>
// bool Array<T>::removeByValue(const T& value){
//     for (int i = 0; i < m_size; ++i){
//         if (m_array[i] == value){
//             return removeByIndex(i);
//         }
//     }
//     return false;
// }

// template<typename T>
// bool Array<T>::removeAllByValue(const T& value){
//     int newSize = 0;

//     for (int i = 0; i < m_size; ++i){
//         if (m_array[i] != value)
//         ++newSize;
//     }

//     int* newArray = new int[newSize];
//     for (int i = 0, j = 0; i < m_size; ++i){
//         if (m_array[i] != value)
//         newArray[j++] = m_array[i];

//     } 

//     delete [] m_array;
//     newArray = m_array;
//     m_size = newSize;
// }

//  template<typename T>
//  T Array<T>::findMaxNumber() const{
//     if (m_size < 0)
//     throw std::runtime_error("Array is empty");
//     int maxNumber = m_array[0];
    
//     for (int i = 0; i < m_size; ++i){
//         if (m_array[i]> maxNumber)
//         maxNumber = m_array[i];
//     }
//     return maxNumber;
//  }

// template<typename T>
// T Array<T>::findMinNumber() const{
//     if (m_size < 0)
//     throw std::runtime_error("Array is empty");
//     int minNumber = m_array[0];
    
//     for (int i = 0; i < m_size; ++i){
//         if (m_array[i] <  minNumber)
//         minNumber = m_array[i];
//     }
//     return minNumber;
//  }

// template<typename T>
// T Array<T>::inputArray(){
//     std::cout << "Enter elements" << std::endl;
//     for (int i = 0; i < m_size; ++i){
//         std::cin >> m_array[i];
//     }
// }

// template<typename T>
// T Array<T>::outputArray() const{
//     for(int i = 0; i < m_size; ++i){
//         std::cout << m_array[i] << std::endl;
//     } 
// }