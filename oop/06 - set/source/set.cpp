#include "set.h"

Set::Set():BoolVector(charSize)
{}

Set::~Set() {}

Set::Set(const char* array, int const size)
 :BoolVector(charSize)
{
 for (int i = 0; i < size; i++)
  addElement(array[i]);
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

Set& Set::operator=(const Set& other) {
    BoolVector::operator=(other); 
    return *this;
}

bool Set::operator==(const Set& other) const {
    return BoolVector::operator==(other);
}

bool Set::operator!=(const Set& other) const
{
 return !(*this == other);
}

Set Set::operator|(const Set& other) const {
    Set result = *this; 
    result |= other;    
    return result;
}

Set& Set::operator|=(const Set& other) {
    BoolVector::operator|=(other); 
    return *this;
}

Set Set::operator&(const Set& other) const {
    Set result = *this; 
    result &= other;    
    return result;
}

Set& Set::operator&=(const Set& other) {
    BoolVector::operator&=(other); 
    return *this;
}

Set Set::operator/(const Set& other) const {
    Set set = (BoolVector::operator&(~other));
    return set;
}

Set& Set::operator/=(const Set& other)
{
  *this = *this / other;
  return *this;
}

Set Set::operator~() const {
    Set result = *this;     
    result.invert();        
    return result;
}

Set Set::operator+(const char ch) const {
    Set result = *this;    
    result.addElement(ch);         
    return result;
}

Set& Set::operator+=(const char ch) {
    addElement(ch);                
    return *this;
}

Set Set::operator-(const char ch) const {
    Set result = *this;     
    result.remove(ch);      
    return result;
}

Set& Set::operator-=(const char ch) {
    remove(ch);             
    return *this;
}

friend std::ostream& operator<<(std::ostream& os, const Set& set) {
  os << "{";
  bool first = true;
  for (int i = 0; i < set.charSize; ++i) {
      if (set.bitValue(i)) {
          if (!first) {
              os << ", ";
          }
          os << static_cast<char>(i + set.start);
          first = false;
          }
  }
  os << "}";
  return os;
}

friend std::istream& operator>>(std::istream& is, Set& set) {
  std::string input;
  is >> input;

  set.setAllBits(false); 
  for (char c : input) {
      if (c != '{' && c != '}' && c != ',' && c != ' ') { 
          set.addElement(c);
          }
        }
  return is;
}


void Set::addElement(const char ch)
{
 setBitValue(ch, true);
}

void Set::removeElement(const char ch)
{
 setBitValue(ch, false);
}
