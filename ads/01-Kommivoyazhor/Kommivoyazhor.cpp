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

bool customNextPermutation(int* arr, int size) {
    return false;
}

int greedyAlgorithm(int** distanceMatrix, int size, int startCity) {
    return 0;
}

void generateReport(int size) {
    
}
