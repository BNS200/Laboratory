#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>

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

bool isSorted(const std::vector<int>& array) {
    for (size_t i = 1; i < array.size(); ++i) {
        if (array[i - 1] > array[i]) {
            return false;
        }
    }
    return true;
}

void heapify(std::vector<int>& array, int n, int i) {
    int largest = i; 
    int left = 2 * i + 1; 
    int right = 2 * i + 2; 

    if (left < n && array[left] > array[largest])
        largest = left;

    if (right < n && array[right] > array[largest])
        largest = right;

    if (largest != i) {
        std::swap(array[i], array[largest]);

        heapify(array, n, largest);
    }
}

void heapSort(std::vector<int>& array) {
    int n = array.size();

    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(array, n, i);

    for (int i = n - 1; i >= 0; --i) {
        std::swap(array[0], array[i]);

        heapify(array, i, 0);
    }
}

int main() {
    for (int i = 10000; i <= 1000000; i *= 10)
        for (int  j = 10; j <= 100000; j *= 100){
            std::vector<int> originalArray = generateRandomArray(i, -j, j);
            
            std::string filename = "array_" + std::to_string(i) + "_" + std::to_string(j) + ".txt";
            writeArrayToFile(filename, originalArray);
            
            double totalTime = 0.0;

            for (int run = 0; run < 3; ++run) {
                std::vector<int> arrCopy = originalArray;
                auto start = std::chrono::high_resolution_clock::now();
            
                heapSort(arrCopy);
            
                auto end = std::chrono::high_resolution_clock::now();
                totalTime += std::chrono::duration<double>(end - start).count();

                if (!isSorted(arrCopy)) {
                    std::cout << "Error: Array is not sorted correctly." << "\n";
                }
            }

        std::cout << "Average time for " << " sort on array of size " << i
                      << " with range " << j << ": " << totalTime / 3.0 << " seconds" << "\n";
    }

    return 0;
}