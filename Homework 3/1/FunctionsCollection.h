#pragma once
#include "PartialFunction.h"

class FunctionsCollection
{
public:
	FunctionsCollection();
	FunctionsCollection(const FunctionsCollection& other);
	FunctionsCollection& operator=(const FunctionsCollection& other);
	~FunctionsCollection();

	FunctionsCollection(FunctionsCollection&& other) noexcept;
	FunctionsCollection& operator=(FunctionsCollection&& other) noexcept;

	void addFunction(PartialFunction* function);
	void addFunction(const PartialFunction& function);

	size_t getSize() const;

	const PartialFunction* operator[](unsigned index) const;
private:
	PartialFunction** data;
	size_t size;
	size_t capacity;

	void free();
	void copyFrom(const FunctionsCollection& other);
	void moveFrom(FunctionsCollection&& other);
	void resize(unsigned newCap);
};