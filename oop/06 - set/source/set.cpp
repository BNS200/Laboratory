#include "set.h"

Set::Set():BoolVector(charSize)
{}

Set::~Set() {}

Set::Set(const char* array, int const size)
 :BoolVector(charSize)
{
 for (int i = 0; i < size; i++)
  m_add(array[i]);
}

Set::Set(const Set& other)
 :BoolVector(other)
{}

const char Set::maxElement() const
{
 for (int i = charSize - 1; i >= 0; i--)
  if (bitValue(i))
   return i;
 return 0;
}

const char Set::minElement() const
{
 for (int i = 0; i < charSize; i++)
  if (bitValue(i))
   return i;
 return 0;
}

bool Set::hasElement(const char ch)
{
 return bitValue(ch);
}

const int Set::power() const
{
 return weight();
}

Set& Set::operator=(const Set& other)
{
 for (int i = 0; i < charSize; i++)
  setBitValue(i, other.bitValue(i));
 return *this;
}

bool Set::operator==(const Set& other) const
{
 for (int i = 0; i < charSize; i++)
  if (bitValue(i) != other.bitValue(i))
   return false;
 return true;
}

bool Set::operator!=(const Set& other) const
{
 return !(*this == other);
}

Set Set::operator|(const Set& other) const
{
 Set setCopy(*this);
 for (int i = 0; i < charSize; i++)
  if (other.bitValue(i))
   setCopy.m_add(i);
 return setCopy;
}

Set& Set::operator|=(const Set& other)
{
    *this = *this | other; 
    return *this;
}

Set Set::operator&(const Set& other) const
{
 Set setCopy;
 for (int i = 0; i < charSize; i++)
  if (other.bitValue(i) && bitValue(i))
   setCopy.m_add(i);
 return setCopy;
}

Set& Set::operator&=(const Set& other)
{
    *this = *this & other; 
    return *this;
}

Set Set::operator/(const Set& other) const
{
 Set setCopy;
 for (int i = 0; i < charSize; i++)
  if (!other.bitValue(i) && bitValue(i))
   setCopy.m_add(i);
 return setCopy;
}

Set& Set::operator/=(const Set& other)
{
    *this = *this / other; 
    return *this;
}

Set Set::operator~() const
{
 Set setCopy;
 for (int i = 0; i < charSize; i++)
  if (!bitValue(i))
   setCopy.m_add(i);
 return setCopy;
}

Set Set::operator+(const char ch) const
{
 Set setCopy = *this;
 setCopy.m_add(ch);
 return setCopy;
}

Set& Set::operator+=(const char ch)
{
    *this = *this + ch; 
    return *this;
}

Set Set::operator-(const char ch) const
{
 Set setCopy = *this;
 setCopy.m_remove(ch);
 return setCopy;
}

Set& Set::operator-=(const char ch)
{
    *this = *this - ch; 
    return *this;
}

