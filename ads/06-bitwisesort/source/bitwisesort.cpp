#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>


void bitwiseSortUnified(std::vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) 
    return; 

    
    int i = 0, j = n - 1;
    while (i <= j) {
        while (i <= j && arr[i] < 0) i++;
        while (i <= j && arr[j] >= 0) j--;
        if (i < j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    
    int negCount = i;

    
    if (negCount > 0) {
        for (int k = 0; k < negCount; ++k) {
            arr[k] = -arr[k]; 
        }

       
        int maxBit = sizeof(int) * 8 - 1; 
        for (int bit = 0; bit <= maxBit; ++bit) {
            int l = 0, r = negCount - 1;
            while (l <= r) {
                while (l <= r && !(arr[l] & (1 << bit))) l++;
                while (l <= r && (arr[r] & (1 << bit))) r--;
                if (l < r) {
                    std::swap(arr[l], arr[r]);
                    l++;
                    r--;
                }
            }
        }

        for (int k = 0; k < negCount; ++k) {
            arr[k] = -arr[k]; 
        }

        
        std::reverse(arr.begin(), arr.begin() + negCount);
    }

    
    if (negCount < n) {
        int maxBit = sizeof(int) * 8 - 1; 
        for (int bit = 0; bit <= maxBit; ++bit) {
            int l = negCount, r = n - 1;
            while (l <= r) {
                while (l <= r && !(arr[l] & (1 << bit))) l++;
                while (l <= r && (arr[r] & (1 << bit))) r--;
                if (l < r) {
                    std::swap(arr[l], arr[r]);
                    l++;
                    r--;
                }
            }
        }
    }
}

bool isSorted(const std::vector<int>& array) {
    for (size_t i = 1; i < array.size(); ++i) {
        if (array[i - 1] > array[i]) {
            return false;
        }
    }
    return true;
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

int main() {
    for (int i = 10000; i <= 1000000; i *= 10) {
        for (int j = 10; j <= 100000; j *= 100) {
            std::vector<int> originalArray = generateRandomArray(i, -j, j);

            int n = originalArray.size();
            std::string filename = "array_" + std::to_string(i) + "_" + std::to_string(j) + ".txt";
            writeArrayToFile(filename, originalArray);

            double totalTime = 0.0;

            for (int run = 0; run < 3; ++run) {
                std::vector<int> arrCopy = originalArray;
                auto start = std::chrono::high_resolution_clock::now();

                bitwiseSortUnified(arrCopy);

                auto end = std::chrono::high_resolution_clock::now();
                totalTime += std::chrono::duration<double>(end - start).count();

                if (!isSorted(arrCopy)) {
                    std::cout << "Error: Array is not sorted correctly." << "\n";
                }
            }

            std::cout << "Average time for bitwise sort on array of size " << i
                      << " with range " << j << ": " << totalTime / 3.0 << " seconds" << "\n";
        }
    }

    return 0;
}