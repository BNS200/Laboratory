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

void writeArrayToFile(const std::string& filename, const std::vector<int>& arr) {
    std::ofstream outFile(filename);
    for (size_t i = 0; i < arr.size(); ++i) {
        outFile << arr[i] << "  ";
    }
}

enum SortType {
    Knuth,
    Normal,
    Hibbard
};


int main() {
    
    std::vector<std::string> sortingNames = {"Knuth", "Normal", "Hibbard"};

    for (int i = 10000; i <= 1000000; i *= 10)
        for (int  j = 10; j <= 100000; j *= 100){
        
        std::vector<int> originalArray = generateRandomArray(i, -j, j);
        
        std::string filename = "array_" + std::to_string(i) + "_" + std::to_string(j) + ".txt";
        writeArrayToFile(filename, originalArray);

        for (size_t index = 0; index < sortingNames.size(); ++index) {
            const auto& sortName = sortingNames[index];
            double totalTime = 0.0;
            for (int run = 0; run < 3; ++run) {
                std::vector<int> arrCopy = originalArray;

                auto start = std::chrono::high_resolution_clock::now();
                
                 switch (index) {
                    case Knuth:
                        shellSortKnuth(arrCopy);
                        break;
                    case Normal:
                        shellSortNormal(arrCopy);
                        break;
                    case Hibbard:
                        shellSortHibbard(arrCopy);
                        break;
                    default:
                        std::cout << "Unknown sorting method" << "\n";
                        continue;
                        }

                auto end = std::chrono::high_resolution_clock::now();
                                totalTime += std::chrono::duration<double>(end - start).count();

                if (!isSorted(arrCopy)) {
                    std::cout << "Error: Array is not sorted correctly using " << sortName << " method" << "\n";
                }
            }
            std::cout << "Average time for " << sortName << " sort on array of size " << i
                      << " with range " << j << ": " << totalTime / 3.0 << " seconds" << "\n";
        }
    }

    return 0;
    }  