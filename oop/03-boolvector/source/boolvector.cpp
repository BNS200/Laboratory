#include "boolvector.h"

BoolVector::Cell BoolVector::_mask(int index)
{
    Cell mask = 1;
	mask <<= CellSize - 1 - (index % CellSize);
	return mask;
}

bool BoolVector::bitValue(int index) const {
    assert(index >= 0 && index < m_length);
    return m_cells[index / CellSize] & _mask(index);
}

BoolVector::BoolVector(int length) : m_length(length) {
    assert(length >= 0);
    m_cellCount = (m_length + CellSize - 1) / CellSize;
    m_cells = new Cell[m_cellCount];
    for (int i = 0; i < m_cellCount; ++i) {
        m_cells[i] = 0;
    }
}

BoolVector::BoolVector(int length, bool value) : m_length(length) {
    assert(length >= 0);
    m_cellCount = (m_length + CellSize - 1) / CellSize;
    m_cells = new Cell[m_cellCount];
    for (int i = 0; i < m_cellCount; ++i) {
        if (value) {
            m_cells[i] = ~0;
        } else {
            m_cells[i] = 0;
        }
    }
}

BoolVector::BoolVector(const BoolVector& other)
{
    m_cellCount = other.m_cellCount;
    m_length = other.m_length;
    m_cells = new Cell[m_cellCount];
    for(int i = 0; i < m_cellCount; i++)
    {
        m_cells[i] = other.m_cells[i];
    }
}


BoolVector::BoolVector(const char* array) {
    assert(array != nullptr);

    m_length = std::strlen(array);
    assert(m_length > 0);

    m_cellCount = (m_length + CellSize - 1) / CellSize;
    m_cells = new Cell[m_cellCount];
    for (int i = 0; i < m_cellCount; ++i) {
        m_cells[i] = 0;
    }

    for (int i = 0; i < m_length; ++i) {
        if (array[i] == '1') {
            setBitValue(i, true);
        } else {
            assert(array[i] == '0');
        }
    }
}

BoolVector::~BoolVector() {
    delete[] m_cells;
}

void BoolVector::setBitValue(int index, bool value) {
    assert(index >= 0 && index < m_length);
    int cellIndex = index / CellSize;
    int bitIndex = index % CellSize;
    if (value) {
        m_cells[cellIndex] |= (1 << bitIndex);
    } else {
        m_cells[cellIndex] &= ~(1 << bitIndex);
    }
}
