#include "StringVector.h"


// BIG 4
void StringVector::copyFrom(const StringVector& other)
{
	vector = new MyString[other.vectorCapacity];
	for (int i = 0; i < other.vectorSize; i++)
	{
		vector[i] = other.vector[i];
	}

	vectorCapacity = other.vectorCapacity;
	vectorSize = other.vectorSize;
}

void StringVector::moveFrom(StringVector&& other)
{
	vector = other.vector;
	other.vector = nullptr;

	vectorCapacity = other.vectorCapacity;
	other.vectorCapacity = 0;

	vectorSize = other.vectorSize;
	other.vectorSize = 0;
}

void StringVector::free()
{
	delete[] vector;
}

StringVector::StringVector()
{
	vector = nullptr;
	vectorCapacity = 0;
	vectorSize = 0;
}

StringVector::StringVector(const StringVector& other)
{
	copyFrom(other);
}

StringVector::StringVector(StringVector&& other)
{
	moveFrom(std::move(other));
}

StringVector& StringVector::operator=(const StringVector& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

StringVector& StringVector::operator=(StringVector&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

StringVector::~StringVector()
{
	free();
}

// Additional Functions
void StringVector::resize(unsigned newAllocatedSize)
{
	MyString* newVector = new MyString[newAllocatedSize + 1];
	for (int i = 0; i < vectorSize; i++)
	{
		newVector[i] = vector[i];
	}
	delete[] vector;
	newVector = vector;
	vectorCapacity = newAllocatedSize;
}

void StringVector::pushBack(const MyString& newString)
{
	if (vectorSize >= vectorCapacity)
	{
		this->resize(vectorCapacity * 2);
	}

	vector[vectorSize + 1] = newString;
	vectorSize++;
}

void StringVector::pushBack(MyString&& newString)
{
	if (vectorSize >= vectorCapacity)
	{
		this->resize(vectorCapacity * 2);
	}

	vector[vectorSize + 1] = std::move(newString);
	vectorSize++;
}

void StringVector::popBack()
{
	if (vectorSize <= vectorCapacity / 4)
	{
		this->resize(vectorCapacity / 2);
	}

	vectorSize--;
}

void StringVector::insert(const MyString& newString, unsigned index)
{
	if (index >= vectorCapacity)
	{
		return;
	}

	if (vectorSize >= vectorCapacity)
	{
		this->resize(vectorCapacity * 2);
	}

	for (int i = vectorSize - 1; i > index; i--)
	{
		vector[i] = vector[i - 1];
	}
	vector[index] = newString;

	vectorSize++;
}

void StringVector::insert(MyString&& newString, unsigned index)
{
	if (index >= vectorCapacity)
	{
		return;
	}

	if (vectorSize >= vectorCapacity)
	{
		this->resize(vectorCapacity * 2);
	}

	for (int i = vectorSize - 1; i > index; i--)
	{
		vector[i] = vector[i - 1];
	}
	vector[index] = std::move(newString);

	vectorSize++;
}

void StringVector::erase(unsigned index)
{
	for (int i = index; i < vectorSize; i--)
	{
		vector[i] = vector[i + 1];
	}
	vectorSize--;
}

void StringVector::clear()
{

}
