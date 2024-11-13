#include <iostream>
#include <cassert>
#include <cstring>
#include <utility>

class BoolVector {
public:

    using Cell = unsigned char;
    static const int CellSize = 8; 

    BoolVector(int length = CellSize);
    BoolVector(int length, bool value);
    BoolVector(const char* array);
    BoolVector(const BoolVector& other);
    ~BoolVector();

    bool bitValue(int index) const;
    void setBitValue(int index, bool value);

private:
    static Cell _mask(int index);

private:
    Cell* m_cells = nullptr;
    int m_cellCount = 0;
    int m_length = 0;
};