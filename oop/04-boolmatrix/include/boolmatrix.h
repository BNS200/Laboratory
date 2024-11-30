#include "boolvector.h"
#include <iostream>
#include <cassert>

class BoolMatrix {
private:
    BoolVector* m_rows; 
    int m_rowCount;     
    int m_colCount;     

public:
    BoolMatrix();                                  
    BoolMatrix(int rows, int cols, bool value = false); 
    BoolMatrix(const BoolMatrix& other);           
    ~BoolMatrix();                                 

   
    int rowCount() const;
    int colCount() const;

    
    void swap(BoolMatrix& other);
    int weight() const;
    int rowWeight(int j) const;
    void invertComponent(int j, int i);

    void invertComponents(int j, int i, int k);
    void setComponent(int j, int i, bool value);
    void setComponents(int j, int i, int k, bool value);
    BoolVector conjunctionAllRows() const;
    BoolVector disjunctionAllRows() const;

};

