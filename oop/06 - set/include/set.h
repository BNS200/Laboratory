#pragma once
#include <iostream>
#include <string>
#include "boolvector.h"

class Set : public BoolVector
{
public:
	Set();
	Set(const char* array, const int size);
	Set(const Set& other);
	~Set();

	const char maxElement() const;
	const char minElement() const;

	bool hasElement(const char ch);
	const int power() const;

	Set operator|(const Set& other) const;
	Set& operator|=(const Set& other);
	Set operator&(const Set& other) const;
	Set& operator&=(const Set& other);
	Set operator/(const Set& other) const;
	Set& operator/=(const Set& other);
	Set operator~() const;
	Set operator+(const char ch) const;
	Set& operator+=(const char ch);
	Set operator-(const char ch) const;
	Set& operator-=(const char ch);

	Set& operator=(const Set& other);

	bool operator==(const Set& other) const;
	bool operator!=(const Set& other) const;
    
	static const int stop = 127;
    static const int start = 32;
    static const int charSize = stop - start;

private:
	void addElement(const char ch);
	void removeElement(const char ch);

}; 