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
    assert(j >= 0 && j < m_rowCount);
    return m_rows[j].weight();
}

int BoolMatrix::columnWeight(int j) const{
    assert(j >= 0 && j < m_rowCount);
	int k = 0;
	for (int i = 0; i < m_rowCount; i++)
		if (m_rows[i].bitValue(j) != 0)
			k++;
	return k;
}


void BoolMatrix::invertComponent(int j, int i) {
    assert(j >= 0 && j < m_rowCount);
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
    assert(j >= 0 && j < m_rowCount);
    m_rows[j].setBitValue(i, value);
}


void BoolMatrix::setComponents(int j, int i, int k, bool value) {
    assert(j >= 0 && j < m_rowCount);
    m_rows[j].setBits(i, k, value);
}


BoolVector BoolMatrix::conjunctionAllRows() const {
    assert(m_rowCount > 0);
    BoolVector result = m_rows[0];
    for (int i = 1; i < m_rowCount; ++i) {
        result &= m_rows[i];
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

BoolMatrix& BoolMatrix::operator=(const BoolMatrix& other) {
    if (this != &other) { 
        delete[] m_rows;
        m_rowCount = other.m_rowCount;
        m_colCount = other.m_colCount;
        m_rows = new BoolVector[m_rowCount];
        for (int i = 0; i < m_rowCount; ++i) {
            m_rows[i] = other.m_rows[i];
        }
    }
    return *this;
}

BoolVector& BoolMatrix::operator[](int index) {
    assert(index >= 0 && index < m_rowCount);
    return m_rows[index];
}

const BoolVector& BoolMatrix::operator[](int index) const {
    assert(index >= 0 && index < m_rowCount);
    return m_rows[index];
}

BoolMatrix BoolMatrix::operator|(const BoolMatrix& other) const {
    BoolMatrix result = *this; 
    result |= other;          
    return result;            
}

BoolMatrix& BoolMatrix::operator|=(const BoolMatrix& other) {
    assert(m_rowCount == other.m_rowCount && m_colCount == other.m_colCount);
    for (int i = 0; i < m_rowCount; ++i) {
        m_rows[i] |= other.m_rows[i];
    }
    return *this;
}

BoolMatrix BoolMatrix::operator^(const BoolMatrix& other) const {
    BoolMatrix result = *this; 
    result ^= other;          
    return result;            
}

BoolMatrix& BoolMatrix::operator^=(const BoolMatrix& other) {
    assert(m_rowCount == other.m_rowCount && m_colCount == other.m_colCount);
    for (int i = 0; i < m_rowCount; ++i) {
        m_rows[i] ^= other.m_rows[i];
    }
    return *this;
}

BoolMatrix BoolMatrix::operator~() const {
    BoolMatrix result = *this;
    for (int i = 0; i < m_rowCount; ++i) {
        result.m_rows[i].invert();  
        }
    return result;
}

std::ostream& operator<<(std::ostream& os, const BoolMatrix& matrix) {
    for (int i = 0; i < matrix.m_rowCount; ++i) {
        os << matrix.m_rows[i] << '\n';
    }
    return os;
}

std::istream& operator>>(std::istream& is, BoolMatrix& matrix) {
    int rows, cols;
    is >> rows >> cols;
    delete[] matrix.m_rows;  
    matrix.m_rowCount = rows;
    matrix.m_colCount = cols;
    matrix.m_rows = new BoolVector[rows];
    for (int i = 0; i < rows; ++i) {
        is >> matrix.m_rows[i]; 
    }
    return is;
}
