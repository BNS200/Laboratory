#pragma once
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <utility>
#include <stdexcept>
#include <random>

template<typename T>

class Array
{
public:
    typedef T* iterator;
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef int difference_type;
    typedef const T* const_iterator;

    typedef size_t size_type;
//     typedef std::reverse_iterator<iterator> reverse_iterator;
//     typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

public:
    Array(int size, const T fillvalue);
    Array(const Array& other);
    Array(Array&& other);
    Array(int size);
    ~Array();


    
    iterator begin();
    iterator end();
    std::reverse_iterator<iterator> rbegin();
    std::reverse_iterator<iterator> rend();
    const iterator begin() const;
    const iterator end() const;
    void outputArray() const;
    void inputArray();
    int getSize() const noexcept;
    bool insert(const int index, const T& value);
    bool insertSeveral(const int& index, const int& count, const T& value);
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
    Array& operator=(const Array& other); 
    Array operator+(const Array& other);
    Array& operator+=(const Array& other);
    bool operator!=(const Array& other) const;
    bool operator==(const Array& other) const;
    void sortArray();
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Array<U>& arr);
    template<typename U>
    friend std::istream& operator>>(std::istream& is, Array<U>& arr);
    void bubbleSort();
    static Array<T> getRandomArray(int size);

  private:
    T* m_array = nullptr;
    int m_size = 0;     
};

template<typename T>
Array<T>::iterator Array<T>::begin(){
    return m_array;
}

template<typename T>
Array<T>::iterator Array<T>::end(){
    return m_array + m_size;
}

template<typename T>
std::reverse_iterator<T*> Array<T>::rbegin(){
    return std::make_reverse_iterator(end());
}

template<typename T>
std::reverse_iterator<T*> Array<T>::rend(){
    return std::make_reverse_iterator(begin());
}

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
Array<T>::Array(Array&& other){
    m_size = std::move(other.m_size);
    m_array = std::move(other.m_array);
    other.m_array = nullptr;
    other.m_size = 0;
}

template<typename T>
Array<T>::~Array() {
    delete[] m_array;
}

template<typename T>
Array<T>::Array(int size) : m_size(size), m_array(nullptr){
    if (size > 0){
        m_array = new T[m_size];
    }
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

bool Array<T>::insertSeveral(const int& index,  const int& count, const T& value){
    if (index < 0){
        throw std::invalid_argument("Index must be > 0");
    }
    T* new_array = new T[m_size + count];
    for (int i = 0; i < index; ++i){
        new_array[i] = m_array[i];
    }
    for (int i = index; i < index + count; ++i){
        new_array[i] = value;
    }
    for (int i = index + count; i < m_size; ++i){
        new_array[i] = m_array[i];
    }

    delete[] m_array;
    m_array = new_array;
    m_size = m_size + count;
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

template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator=(const Array<ItemType>& other)
{
	if (m_size == other.m_size)
	{
		for (int i = 0; i < m_size; ++i)
		{
			m_array[i] = other.m_array[i];
		}
	}
	else
	{
		Array<ItemType> copy(other);
		swap(copy);
	}
	return *this;
}

template<typename T>
Array<T> Array<T>::operator+(const Array<T>& other){
    Array result(m_size + other.m_size);
    for (int i = 0; i < m_size; ++i){
        result[i] = m_array[i];
    }

    for (int i = 0;i < other.m_size; ++i){
        result[m_size + i] = other[i];
    }
    return result;
}

template <typename T>
Array<T>& Array<T>::operator+=(const Array<T>& other)
{
    *this = std::move(*this + other);
    return *this;
}

template<typename T>
bool Array<T>::operator==(const Array<T>& other) const{
    if (m_size != other.m_size)
        return false;
    for (int i = 0; i < m_size; ++i){
        m_array[i] != other[i]; 
        return false;
    } 
    return true;   
} 

template<typename T>
bool Array<T>::operator!=(const Array<T>& other) const{
    return !(*this == other);
}

template<typename T>
void Array<T>::sortArray() {
        std::sort(begin(), end());
}

template<typename T>
void Array<T>::bubbleSort(){
    for (int i = 0; i < m_size - 1; ++i){
        bool swaped = false;
        for(int j = 0; j < m_size - i - 1; ++j){
            if (m_array[j] > m_array[j + 1]){
                std::swap(m_array[j], m_array[j+1]);
            }
            swaped = true;
        }
        if (!swaped)
            break;
    }
}

template<typename T>
Array<T> Array<T>::getRandomArray(int size){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 100);
    Array<T> arr(size);
    for (int i = 0; i < size; ++i ){
        arr[i] = distribution(gen);
    }
    return arr;
}


template<typename T>
std::istream& operator>>(std::istream& is, Array<T>& arr) {
    for (int i = 0; i < arr.getSize(); ++i) {
        is >> arr[i];
    }
    return is;
    }

template<typename T>
std::ostream& operator<<(std::ostream& os, const Array<T>& arr) {
    for (int i = 0; i < arr.getSize(); i++)
		os << arr[i] << " ";
	return os;
    }

