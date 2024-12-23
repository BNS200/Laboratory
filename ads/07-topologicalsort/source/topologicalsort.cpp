#include "boolmatrix.h"
#include <iostream>
#include <queue>
#include <vector>
#include <stdexcept>

std::vector<int> topologicalSort(const BoolMatrix& matrix) {
    int n = matrix.rowCount(); 
    std::vector<int> inDegree(n, 0);   
    std::vector<int> result;          
    
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            if (matrix[i][j]) { 
                inDegree[j]++;
            }
        }
    }

    std::queue<int> zeroInDegree;
    for (int i = 0; i < n; ++i) {
        if (inDegree[i] == 0) {
            zeroInDegree.push(i);
        }
    }

    while (!zeroInDegree.empty()) {
        int element = zeroInDegree.front();
        zeroInDegree.pop();
        result.push_back(element);

        for (int v = 0; v < n; ++v) {
            if (matrix[element][v]) { 
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    zeroInDegree.push(v);
                }
            }
        }
    }

    if (result.size() != n) {
        throw std::runtime_error("The graph contains a cycle! Topological sorting is not possible.");
    }

    return result;
}