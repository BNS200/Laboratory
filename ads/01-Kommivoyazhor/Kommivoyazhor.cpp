#include <iostream>


void generateReport(int size);

int main() {
    srand(time(0));
    for (int size = 4; size <= 10; ++size) {
        generateReport(size);
    }
    return 0;
}


int calculatePathCost(int** distanceMatrix, int* path, int size) {
    int cost = 0;
    for (int i = 0; i < size - 1; ++i) {
        cost += distanceMatrix[path[i]][path[i + 1]];
    }
    cost += distanceMatrix[path[size - 1]][path[0]];
    return cost;
}

bool nextPermutation(int* array, int size) {
    int k = -1;
    for (int i = 0; i < size - 1; ++i) {
        if (array[i] < array[i + 1]) {
            k = i;
        }
    }

    if (k == -1) {
        return false;
    }

    int l = -1;
    for (int i = k + 1; i < size; ++i) {
        if (array[k] < array[i]) {
            l = i;
        }
    }

    int temp = array[k];
    array[k] = array[l];
    array[l] = temp;

    for (int left = k + 1, right = size - 1; left < right; ++left, --right) {
        temp = array[left];
        array[left] = array[right];
        array[right] = temp;
    }

    return true;
}

int greedyAlgorithm(int** distanceMatrix, int size, int startCity) {
    return 0;
}

void generateReport(int size) {
    
}
