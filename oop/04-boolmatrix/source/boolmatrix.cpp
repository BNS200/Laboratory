#include "boolmatrix.h"


BoolMatrix::BoolMatrix() : m_rows(nullptr), m_rowCount(0), m_colCount(0) {}


BoolMatrix::BoolMatrix(int rows, int cols, bool value) 
    : m_rowCount(rows), m_colCount(cols) {
    m_rows = new BoolVector[m_rowCount];
    for (int i = 0; i < m_rowCount; ++i) {
        m_rows[i] = BoolVector(m_colCount, value);
    }
}


BoolMatrix::BoolMatrix(const BoolMatrix& other) 
    : m_rowCount(other.m_rowCount), m_colCount(other.m_colCount) {
    m_rows = new BoolVector[m_rowCount];
    for (int i = 0; i < m_rowCount; ++i) {
        m_rows[i] = other.m_rows[i];
    }
}


BoolMatrix::~BoolMatrix() {
    delete[] m_rows;
}


int BoolMatrix::rowCount() const {
    return m_rowCount;
}


int BoolMatrix::colCount() const {
    return m_colCount;
}


void BoolMatrix::swap(BoolMatrix& other) {
    std::swap(m_rows, other.m_rows);
    std::swap(m_rowCount, other.m_rowCount);
    std::swap(m_colCount, other.m_colCount);
}


int BoolMatrix::weight() const {
    int totalWeight = 0;
    for (int i = 0; i < m_rowCount; ++i) {
        totalWeight += m_rows[i].weight();
    }
    return totalWeight;
}


int BoolMatrix::rowWeight(int j) const {
    assert(j >= 0 & j < m_rowCount);
    return m_rows[j].weight();
}


void BoolMatrix::invertComponent(int j, int i) {
    assert(j >= 0 & j < m_rowCount);
    m_rows[j].invert(i);
}


