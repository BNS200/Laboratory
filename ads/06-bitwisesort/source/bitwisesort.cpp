#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>

void bitwiseSort(std::vector<int>& arr, int l, int r, int k) {
    if (l >= r || k < 0) {
        return;
    }

    int i = l, j = r;
    while (i <= j) {
        while (i <= j && !(arr[i] & (1 << k))) {
            i++;
        }
        while (i <= j && (arr[j] & (1 << k))) {
            j--;
        }
        if (i < j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    bitwiseSort(arr, l, j, k - 1);
    bitwiseSort(arr, i, r, k - 1);
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

            int offset = j;
            for (size_t index = 0; index < originalArray.size(); ++index) {
                originalArray[index] += offset;
            }

            int n = originalArray.size();
            int maxBit = sizeof(int) * 8 - 1; 
            std::string filename = "array_" + std::to_string(i) + "_" + std::to_string(j) + ".txt";
            writeArrayToFile(filename, originalArray);

            double totalTime = 0.0;

            for (int run = 0; run < 3; ++run) {
                std::vector<int> arrCopy = originalArray;
                auto start = std::chrono::high_resolution_clock::now();

                bitwiseSort(arrCopy, 0, n - 1, maxBit);

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