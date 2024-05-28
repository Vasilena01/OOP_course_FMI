#include "Functionscollection.h"

FunctionsCollection::FunctionsCollection()
{
	capacity = 8;
	data = new PartialFunction * [capacity] {nullptr};
	size = 0;
}

FunctionsCollection::FunctionsCollection(const FunctionsCollection& other)
{
	copyFrom(other);
}

FunctionsCollection& FunctionsCollection::operator=(const FunctionsCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

FunctionsCollection::FunctionsCollection(FunctionsCollection&& other) noexcept
{
	moveFrom(std::move(other));
}

FunctionsCollection& FunctionsCollection::operator=(FunctionsCollection&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

FunctionsCollection::~FunctionsCollection()
{
	free();
}

void FunctionsCollection::addFunction(PartialFunction* function)
{
	if (size == capacity)
		resize(capacity * 2);

	data[size++] = function;
	function = nullptr;
}

void FunctionsCollection::addFunction(const PartialFunction& function)
{
	PartialFunction* cloned = function.clone();
	addFunction(cloned);
}

size_t FunctionsCollection::getSize() const
{
	return size;
}

const PartialFunction* FunctionsCollection::operator[](unsigned index) const
{
	return data[index];
}

void FunctionsCollection::free()
{
	for (int i = 0; i < size; i++)
		delete data[i];
	delete[] data;
}

void FunctionsCollection::copyFrom(const FunctionsCollection& other)
{
	data = new PartialFunction * [other.capacity];

	for (int i = 0; i < other.size; i++)
		data[i] = other.data[i]->clone();

	size = other.size;
	capacity = other.capacity;
}

void FunctionsCollection::moveFrom(FunctionsCollection&& other)
{
	data = other.data;
	other.data = nullptr;

	size = other.size;
	capacity = other.capacity;

	other.size = other.capacity = 0;
}

void FunctionsCollection::resize(unsigned newCap)
{
	PartialFunction** newData = new PartialFunction * [newCap];
	for (int i = 0; i < size; i++)
		newData[i] = data[i];
	delete[] data;
	data = newData;
	capacity = newCap;
}
