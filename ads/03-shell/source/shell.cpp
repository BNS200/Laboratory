#include <iostream>
#include <vector>


bool isSorted(std::vector<int>& arr){
    for (int i = 0;i < arr.size(); ++i){
        if (arr[i] > arr[i+1])
        return false;
    }
    return true;
}

void shellSortKnuth(std::vector<int>& arr){
    int sizeArr = arr.size();
    int gap = 1;
    while(gap < sizeArr / 3)
        gap = 3 * gap + 1;

    while (gap >= 1)
    {
        for (int i = gap; i < sizeArr; ++i){
            for (int j = i;j >= gap && arr[j] < arr[j - gap]; j -= gap){
                std::swap(arr[j], arr[j - gap]);
            }
        }
        gap /= 3;    
    }
} 

void shellSortNormal(std::vector<int>& arr){
    int sizeArr = arr.size();
    int gap = 1;
    while (gap < sizeArr / 2)
    gap = 2 * gap + 1;

    while(gap >= 1)
    {
        for (int i = gap; i < sizeArr; ++i){
            for (int j = i; j >= gap && arr[j] < arr[j - gap]; j -= gap){
                std::swap(arr[j], arr[j - gap]); 
            }
        }
        gap /= 2;
    }
}

void shellSortHibbard(std::vector<int>& array) {
    int arraySize = array.size();
    int gap = 1;
    
    while ((gap * 2) - 1 < arraySize) {
        gap = (gap * 2) - 1;
    }

    while (gap >= 1) {
        for (int i = gap; i < arraySize; ++i) {
            for (int j = i; j >= gap && array[j] < array[j - gap]; j -= gap) {
                std::swap(array[j], array[j - gap]);
            }
        }
        gap = (gap + 1) / 2 - 1;
    }
}
int main() {
    return 0;
}

