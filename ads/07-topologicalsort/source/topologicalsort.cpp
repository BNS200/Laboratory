#include "boolmatrix.h"
#include <iostream>
#include <vector>
#include <stdexcept>

bool addEdge(BoolMatrix& matrix, int from, int to) {
    if (from <= 0 || to <= 0) 
        return false;
    matrix.setComponent(from - 1, to - 1, true);
    return true;
}


bool topologicalSort(BoolMatrix& matrix, std::vector<int>& result) {
    int n = matrix.rowCount(); 
    int m = matrix.colCount(); 
    
    BoolVector v0(n, false); 
    BoolVector v1(n, false); 
    BoolVector v2(n, false); 

    
    v1 = matrix.disjunctionAllRows(); 
    v0 = ~v1;                     
    for (int i = 0; i < n; ++i) {
        if (v0[i]) { 
            result.push_back(i + 1); 
            for (int j = 0; j < m; ++j) {
                matrix.setComponent(i, j, false); 
            }
        }
    }

    
    while (v0.weight() != v0.length()) { 
        v1 = matrix.disjunctionAllRows();
        v2 = ~v1 & ~v0;                 
        if (v2.weight() == 0) {         
            return false;               
        }

        for (int i = 0; i < n; ++i) {
            if (v2[i]) {                
                v0[i] = true;           
                result.push_back(i + 1); 

                for (int j = 0; j < m; ++j) {
                    matrix.setComponent(i, j, false);
                }
            }
        }
    }

    return true; 
}

int main() {
    BoolMatrix matrix(6, 6);

    
    addEdge(matrix, 1, 2);
    addEdge(matrix, 1, 3);
    addEdge(matrix, 3, 4);
    addEdge(matrix, 2, 5);
    addEdge(matrix, 4, 5);
    addEdge(matrix, 5, 6);

    
    std::vector<int> sorted;
    if (topologicalSort(matrix, sorted)) {
        for (int i = 0; i < sorted.size(); ++i) {
            std::cout << sorted[i] << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "The graph contains a cycle. Topological sorting is not possible." << std::endl;
    }

    return 0;
}
