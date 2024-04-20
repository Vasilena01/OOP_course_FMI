#pragma once
#include <iostream>
#include "MyString.h"

class StringVector
{
public:
	StringVector();
	StringVector(const StringVector& other);
	StringVector(StringVector&& other) noexcept;
	StringVector& operator=(const StringVector& other);
	StringVector& operator=(StringVector&& other) noexcept;
	~StringVector();

	void resize(unsigned newAllocatedSize);
	void pushBack(const MyString& newString);
	void pushBack(MyString&& newString);
	void popBack();
	void insert(const MyString& newString, unsigned index);
	void insert(MyString&& newString, unsigned index);
	void erase(unsigned index);
	void clear();
private:
	MyString* vector;
	unsigned vectorCapacity; //max vector capacity
	unsigned vectorSize; // current vector size

	void copyFrom(const StringVector& other);
	void moveFrom(StringVector&& other);
	void free();
};

