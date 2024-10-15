#pragma once
#include <iostream>
#include <assert.h>


template<typename T>
class Array
{
public:
    Array(int size, const T fillvalue = T());
    Array(const Array& other);
    Array(Array&& other);
    ~Array();

    void outputArray() const;
    void inputArray();
    int getSize() const noexcept;
    bool insert(const int index, const T& value);
    int findFirstOccurrence(const T& value) const;
    bool removeByIndex(const int index);
    bool removeByValue(const T& value);
    bool removeAllByValue(const T& value);
    T findMaxNumber() const;
    T findMinNumber() const;
    T& operator[](int index);
    const T& operator[](int index) const;
    void swap(Array& other) noexcept;
    Array& operator=(Array&& other); 
    Array& operator+(Array& other);
    Array& operator+=(const Array& other);
    bool operator!=(Array& other);
    bool operator==(Array& other);
private:
    T* m_array = nullptr;
    int m_size = 0;     
};

template<typename T>
Array<T>::Array(int size, const T fillvalue) {
    if (size < 0) {
        size = -size;
    }
    m_size = size;
    m_array = new T[m_size];
    for (int i = 0; i < m_size; ++i) {
        m_array[i] = fillvalue;
    }
}

template<typename T>
Array<T>::Array(const Array& other) {
    m_size = other.m_size;
    m_array = new T[m_size];
    for (int i = 0; i < m_size; ++i) {
        m_array[i] = other.m_array[i];
    }
}

template<typename T>
Array<T>::Array(Array&& other):
    m_size(std::move(other.m_size)),
    m_array(std::move(other.m_array))
{
}

template<typename T>
Array<T>::~Array() {
    delete[] m_array;
}

template<typename T>
bool Array<T>::insert(const int index, const T& value)
{
    if (index < 0 || index > m_size)
        return false;

    T* newArray = new T[m_size + 1];
    for (int i = 0; i < index; ++i)
        newArray[i] = m_array[i];

    newArray[index] = value;
    for (int i = index + 1; i <= m_size; ++i)
        newArray[i] = m_array[i - 1];

    delete[] m_array;
    m_array = newArray;
    m_size++;

    return true;
}

template<typename T>
int Array<T>::getSize() const noexcept {
    return m_size;
}

template<typename T>
int Array<T>::findFirstOccurrence(const T& value) const {
    for (int i = 0; i < m_size; ++i) {
        if (m_array[i] == value) {
            return i;
        }
    }
    return -1;
}

template<typename T>
bool Array<T>::removeByIndex(int index) {
    if (index < 0 || index >= m_size) {
        return false;
    }
    
    T* newArray = new T[m_size - 1];
    
    for (int i = 0; i < index; ++i) {
        newArray[i] = m_array[i];
    }
    for (int i = index; i < m_size - 1; ++i) {
        newArray[i] = m_array[i + 1];
    }

    delete[] m_array;
    m_array = newArray;
    --m_size;

    return true;
}

template<typename T>
bool Array<T>::removeByValue(const T& value) {
    for (int i = 0; i < m_size; ++i) {
        if (m_array[i] == value) {
            return removeByIndex(i);
        }
    }
    return false;
}

template<typename T>
bool Array<T>::removeAllByValue(const T& value) {
    int newSize = 0;
    bool found = false;

    for (int i = 0; i < m_size; ++i) {
        if (m_array[i] != value)
            ++newSize;
        else {
            found = true;
        }
    }

    if (!found)
        return false;

    T* newArray = new T[newSize];
    for (int i = 0, j = 0; i < m_size; ++i) {
        if (m_array[i] != value)
            newArray[j++] = m_array[i];
    }

    delete[] m_array;
    m_array = newArray;
    m_size = newSize;
    return true;
}

template<typename T>
T Array<T>::findMaxNumber() const {
    if (m_size <= 0)
        throw std::runtime_error("Array is empty");
    
    T maxNumber = m_array[0];
    
    for (int i = 1; i < m_size; ++i) {
        if (m_array[i] > maxNumber)
            maxNumber = m_array[i];
    }
    
    return maxNumber;
}

template<typename T>
T Array<T>::findMinNumber() const {
    if (m_size <= 0)
        throw std::runtime_error("Array is empty");
    
    T minNumber = m_array[0];
    
    for (int i = 1; i < m_size; ++i) { 
        if (m_array[i] < minNumber)
            minNumber = m_array[i];
    }
    
    return minNumber;
}

template<typename T>
void Array<T>::inputArray() { 
    std::cout << "Enter elements" << std::endl;
    for (int i = 0; i < m_size; ++i) {
        std::cin >> m_array[i];
    }
}

template<typename T>
void Array<T>::outputArray() const { 
    for (int i = 0; i < m_size; ++i) {
        std::cout << m_array[i] << std::endl;
    }
}

template<typename T>
T& Array<T>::operator[](int index){
    assert(index >= 0 && index < m_size);
    return m_array[index];
}

template <typename T>
const T& Array<T>::operator[](int index) const
{
    assert(index >= 0 && index < m_size);
    return m_array[index];
}

template <typename T>
void Array<T>::swap(Array& other) noexcept
{
    std::swap(m_size, other.m_size);
    std::swap(m_array, other.m_array);
}

template<typename T>
Array<T>&  Array<T>::operator=(Array&& other){
    swap(other); 
    return *this;
}

template<typename T>
Array<T>& Array<T>::operator+(Array& other){
    Array result(m_size + other.m_size);
    for (int i = 0; i < m_size; ++i){
        result[i] = m_array[i];
    }

    for (int i = 0;i < other.m_size; ++i){
        result[m_size + i] == other[i];
    }
}

template <typename T>
Array<T>& Array<T>::operator+=(const Array& other)
{
    operator+(other).swap(*this);
    return *this;
}

template<typename T>
bool Array<T>::operator==(Array& other){
    if (m_size != other.m_size)
        return false;
    for (int i = 0; i < m_size; ++i){
        m_array[i] != other[i]; 
        return false;
    } 
    return true;   
} 

template<typename T>
bool Array<T>::operator!=(Array& other){
    return !(*this == other);
}