#include <iostream>
#include <chrono>
#include <climits>
#include <cstdlib>

int** generateDistanceMatrix(int size) {
    int** distanceMatrix = new int*[size];
    for (int i = 0; i < size; ++i) {
        distanceMatrix[i] = new int[size];
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i != j) {
                distanceMatrix[i][j] = rand() % 10 + 1;
            } else {
                distanceMatrix[i][j] = 0;
            }
        }
    }

    return distanceMatrix;
}

void printDistanceMatrix(int** distanceMatrix, int size) {
    std::cout << "Matrix distance:\n";
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << distanceMatrix[i][j] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
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

int greedyAlgorithm(int** distanceMatrix, int size, int startCity, int* path) {
    bool* visited = new bool[size]();
    visited[startCity] = true;
    path[0] = startCity;
    
    int currentCity = startCity;
    int totalCost = 0;

    for (int i = 1; i < size; ++i) {
        int nextCity = -1;
        int minCost = INT_MAX;

        for (int j = 0; j < size; ++j) {
            if (!visited[j] && distanceMatrix[currentCity][j] < minCost) {
                minCost = distanceMatrix[currentCity][j];
                nextCity = j;
            }
        }

        path[i] = nextCity;
        visited[nextCity] = true;
        totalCost += minCost;
        currentCity = nextCity;
    }

    totalCost += distanceMatrix[currentCity][startCity]; 

    delete[] visited;

    return totalCost;
}

void generateReport(int size) {
    int** distanceMatrix = generateDistanceMatrix(size);
    printDistanceMatrix(distanceMatrix, size);

    int startCity = rand() % size;

    int* cities = new int[size - 1];
    for (int i = 0, j = 0; i < size; ++i) {
        if (i != startCity) {
            cities[j++] = i;
        }
    }

    int exactSolutionCost = INT_MAX;
    int worstSolutionCost = 0;

    int* bestPath = new int[size];
    int* worstPath = new int[size];

    auto startTimeExact = std::chrono::high_resolution_clock::now();

    do {
        int* fullPath = new int[size];
        fullPath[0] = startCity;
        
        for (int i = 0; i < size - 1; ++i) {
            fullPath[i + 1] = cities[i];
        }

        int currentCost = calculatePathCost(distanceMatrix, fullPath, size);
        if (currentCost < exactSolutionCost) {
            exactSolutionCost = currentCost;
                for (int i = 0; i < size; ++i) {
                    bestPath[i] = fullPath[i];
                }
        }
        if (currentCost > worstSolutionCost) {
            worstSolutionCost = currentCost;
                for (int i = 0; i < size; ++i) {
                    worstPath[i] = fullPath[i];
                 }
        }           

        delete[] fullPath;
    } while (nextPermutation(cities, size - 1));

    auto endTimeExact = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> timeExact = endTimeExact - startTimeExact;

    auto startTimeGreedy = std::chrono::high_resolution_clock::now();
    
    int* greedyPath = new int[size];
    int greedySolutionCost = greedyAlgorithm(distanceMatrix, size, startCity, greedyPath);

    auto endTimeGreedy = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> timeGreedy = endTimeGreedy - startTimeGreedy;

    double qualityGreedySolution = (1.0 - static_cast<double>(greedySolutionCost - exactSolutionCost) / (worstSolutionCost - exactSolutionCost)) * 100.0;

    std::cout << "Matrix size: " << size << "x" << size << "\n";
    std::cout << "- Start city: " << startCity << "\n";
    
    std::cout << "- Exact solution cost: " << exactSolutionCost << "\n";
    std::cout << "- Exact path: ";
    for (int i = 0; i < size; ++i) {
        std::cout << bestPath[i] << " ";
    }
    std::cout << "\n";

    std::cout << "- Worst solution cost: " << worstSolutionCost << "\n";
    std::cout << "- Worst path: ";
    for (int i = 0; i < size; ++i) {
        std::cout << worstPath[i] << " ";
    }
    std::cout << "\n";

    std::cout << "- Exact solution time: " << timeExact.count() << " seconds\n";
    
    std::cout << "- Greedy solution cost: " << greedySolutionCost << "\n";
    std::cout << "- Greedy path: ";
    for (int i = 0; i < size; ++i) {
        std::cout << greedyPath[i] << " ";
    }
    std::cout << "\n";
        std::cout << "- Greedy solution time: " << timeGreedy.count() << " seconds\n";
    std::cout << "- Quality of greedy solution: " << qualityGreedySolution << "%\n";

    delete[] bestPath;
    delete[] worstPath;
    delete[] greedyPath;
    delete[] cities;

    for (int i = 0; i < size; ++i) {
        delete[] distanceMatrix[i];
    }
    delete[] distanceMatrix;
}

int main() {
    srand(time(0));
    for (int size = 4; size <= 10; ++size) {
        generateReport(size);
    }
    return 0;
}