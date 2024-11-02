#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>

bool isSorted(const std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

void shellSortKnuth(std::vector<int>& arr) {
    int sizeArr = arr.size();
    int gap = 1;
    while (gap < sizeArr / 3) {
        gap = 3 * gap + 1;
    }

    while (gap >= 1) {
        for (int i = gap; i < sizeArr; ++i) { 
            for (int j = i; j >= gap && arr[j] < arr[j - gap]; j -= gap) {
                std::swap(arr[j], arr[j - gap]);
            }
        }
        gap /= 3;
    }
}


void shellSortNormal(std::vector<int>& arr) {
    int sizeArr = arr.size();
    int gap = sizeArr / 2; 

    while (gap > 0) {
        for (int i = gap; i < sizeArr; ++i) { 
            for (int j = i; j >= gap && arr[j] < arr[j - gap]; j -= gap) {
                std::swap(arr[j], arr[j - gap]);
            }
        }
        gap /= 2;
    }
}


void shellSortHibbard(std::vector<int>& array) {
    int arraySize = array.size();
    int k = 1;
    int gap = 1;

    while ((1 << k) - 1 < arraySize) { 
        k++;
        gap = (1 << k) - 1;
    }

    while (gap >= 1) {
        for (int i = gap; i < arraySize; ++i) { 
            for (int j = i; j >= gap && array[j] < array[j - gap]; j -= gap) {
                std::swap(array[j], array[j - gap]);
            }
        }
        k--;
        gap = (1 << k) - 1;
    }
}

std::vector<int> generateRandomArray(int size, int minValue, int maxValue) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(minValue, maxValue);

    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }

    return arr;
}

int main() {
    return 0;
}
