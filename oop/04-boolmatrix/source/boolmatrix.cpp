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

void BoolMatrix::invertComponents(int j, int i, int k) {
    assert(j >= 0 && j < m_rowCount);
    assert(i >= 0 && i + k <= m_colCount);
    BoolVector& row = m_rows[j];
    for (int index = i; index < i + k; ++index) {
        row[index] = ~row[index];
    }
}

void BoolMatrix::setComponent(int j, int i, bool value) {
    assert(j >= 0 & j < m_rowCount);
    m_rows[j].setBitValue(i, value);
}


void BoolMatrix::setComponents(int j, int i, int k, bool value) {
    assert(j >= 0 & j < m_rowCount);
    m_rows[j].setBits(i, k, value);
}


BoolVector BoolMatrix::conjunctionAllRows() const {
    assert(m_rowCount > 0);
    BoolVector result = m_rows[0];
    for (int i = 1; i < m_rowCount; ++i) {
        result = m_rows[i];
    }
    return result;
}


BoolVector BoolMatrix::disjunctionAllRows() const {
    assert(m_rowCount > 0);
    BoolVector result = m_rows[0];
    for (int i = 1; i < m_rowCount; ++i) {
        result |= m_rows[i];
    }
    return result;
}
