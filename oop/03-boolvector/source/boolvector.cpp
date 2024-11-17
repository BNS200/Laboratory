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

void BoolVector::swap(BoolVector& other) {
    std::swap(m_cells, other.m_cells);
    std::swap(m_cellCount, other.m_cellCount);
    std::swap(m_length, other.m_length);
}

void BoolVector::invert() {
    for (int i = 0; i < m_cellCount; ++i) {
        m_cells[i] = ~m_cells[i];
    }
}

void BoolVector::invert(int index) {
    assert(index >= 0 && index < m_length);
    m_cells[index / CellSize] ^= _mask(index);
}

void BoolVector::setBits(int index, int count, bool value) {
    assert(index >= 0 && index + count <= m_length);
    for (int i = index; i < index + count; ++i) {
        setBitValue(i, value);
    }
}
void BoolVector::setAllBits(bool value) {
    for (size_t i = 0; i < m_cellCount; ++i) {
        if (value) {
            m_cells[i] = ~0; 
        } else {
            m_cells[i] = 0;
        }
    }
}

int BoolVector::weight() const {
    int count = 0;
    for (int i = 0; i < m_length; ++i) {
        if (bitValue(i)) {
            ++count;
        }
    }
    return count;
}

BoolVector& BoolVector::operator=(const BoolVector& other) {
    if (this != &other) {
        delete[] m_cells;
        m_cellCount = other.m_cellCount;
        m_length = other.m_length;
        m_cells = new Cell[m_cellCount];
        for (size_t i = 0; i < m_cellCount; ++i) {
            m_cells[i] = other.m_cells[i];
        }
    }
    return *this;
}

BoolVector BoolVector::operator&(const BoolVector& other) const
{
 assert(m_length == other.m_length);
 BoolVector result(m_length);
 for (int i = 0; i < m_cellCount; ++i) {
     result.m_cells[i] = m_cells[i] & other.m_cells[i];
 }
 return result;
}

BoolVector& BoolVector::operator&=(const BoolVector& other)
{
 assert(m_length == other.m_length);
 for (int i = 0; i < m_cellCount; ++i) {
     m_cells[i] &= other.m_cells[i];
 }
 return *this;
}

BoolVector BoolVector::operator|(const BoolVector& other) const
{
 assert(m_length == other.m_length);
 BoolVector result(m_length);
 for (int i = 0; i < m_cellCount; ++i) {
     result.m_cells[i] = m_cells[i] | other.m_cells[i];
 }
 return result;
}

BoolVector& BoolVector::operator|=(const BoolVector& other)
{
 assert(m_length == other.m_length);
 for (int i = 0; i < m_cellCount; ++i) {
     m_cells[i] |= other.m_cells[i];
 }
 return *this;
}

BoolVector BoolVector::operator^(const BoolVector& other) const
{
 assert(m_length == other.m_length);
 BoolVector result(m_length);
 for (int i = 0; i < m_cellCount; ++i) {
     result.m_cells[i] = m_cells[i] ^ other.m_cells[i];
 }
 return result;
}

BoolVector& BoolVector::operator^=(const BoolVector& other)
{
 assert(m_length == other.m_length);
 for (int i = 0; i < m_cellCount; ++i) {
     m_cells[i] ^= other.m_cells[i];
 }
 return *this;
}

BoolVector BoolVector::operator~() const
{
 BoolVector result(*this);
 result.invert();
 return result;
}

BoolVector BoolVector::operator<<(int shift) const
{
 if (shift <= 0 || shift >= m_length) 
    return *this;
 BoolVector result(m_length);
 for (int i = shift; i < m_length; ++i) {
     if (bitValue(i - shift)) {
         result.setBitValue(i, true);
     }
 }
 return result;
}

BoolVector& BoolVector::operator<<=(int shift)
{
 *this = *this << shift;
 return *this;
}

BoolVector BoolVector::operator>>(int shift) const
{
 if (shift <= 0 || shift >= m_length) return *this;

 BoolVector result(m_length);

 for (int i = 0; i < m_length - shift; ++i) {
     if (bitValue(i + shift)) {
         result.setBitValue(i, true);
     }
 }

 return result;
}

BoolVector& BoolVector::operator>>=(int shift)
{
 *this = *this >> shift;
 return *this;
}

std::ostream& operator<<(std::ostream& os, const BoolVector& bv) {
    for (int i = 0; i < bv.m_length; ++i) {
        os << bv.bitValue(i);
    }
    return os;
}

std::istream& operator>>(std::istream& is, BoolVector& bv) {
    for (int i = 0; i < bv.m_length; ++i) {
        char bit;
        is >> bit;
        bv.setBitValue(i, bit == '1');
    }
    return is;
}

BoolVector::Rank BoolVector::operator[](int index)
{
 assert(index >= 0 && index < m_length);
 return Rank(&m_cells[index / CellSize], _mask(index));
}

BoolVector::Rank::Rank(Cell* cell, Cell mask)
 : m_cell(cell), m_mask(mask)
{
 assert(m_cell != nullptr);
 assert(m_mask > 0);
}

BoolVector::Rank& BoolVector::Rank::operator=(const Rank& other)
{
 return operator=(static_cast<bool>(other));
}

BoolVector::Rank& BoolVector::Rank::operator=(bool value)
{
 if (value) {
     *m_cell |= m_mask;
 } else {
     *m_cell &= ~m_mask;
 }
 return *this;
}

BoolVector::Rank::operator bool() const
{
 return (*m_cell & m_mask) != 0;
}