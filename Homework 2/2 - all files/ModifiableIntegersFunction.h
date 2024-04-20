#pragma once
#include <iostream>
#include "Point.h"
#include "GlobalConstants.h"

typedef int16_t(*FunctionPointer)(int16_t);

class ModifiableIntegersFunction
{
public:
	ModifiableIntegersFunction();
	ModifiableIntegersFunction(FunctionPointer f);
	ModifiableIntegersFunction(const ModifiableIntegersFunction& other);
	ModifiableIntegersFunction(ModifiableIntegersFunction&& other) noexcept;
	ModifiableIntegersFunction& operator=(const ModifiableIntegersFunction& other);
	ModifiableIntegersFunction& operator=(ModifiableIntegersFunction&& other) noexcept;
	~ModifiableIntegersFunction();

	void setModification(int16_t valueToModify, int16_t newValue);
	void disableValue(int16_t valueToDisable);
	int16_t operator()(int16_t input) const;
	ModifiableIntegersFunction operator()(const ModifiableIntegersFunction& other) const;
	ModifiableIntegersFunction operator^(int times) const;
	ModifiableIntegersFunction& operator+=(const ModifiableIntegersFunction& other);
	ModifiableIntegersFunction& operator-=(const ModifiableIntegersFunction& other);
	void serializeInBinaryFile(const char* fileName);
	void deserializeFromBinaryFile(const char* fileName);
	void printInInterval(int16_t x1, int16_t y1) const;

	friend bool operator>(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
	friend bool operator<(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
	friend bool operator==(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
	friend bool operator!=(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
	friend bool operator||(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
	friend ModifiableIntegersFunction inverse(const ModifiableIntegersFunction& other);
	friend bool isInjective(const ModifiableIntegersFunction& other);
	friend bool isSurjective(const ModifiableIntegersFunction& other);
	friend bool isBijective(const ModifiableIntegersFunction& other);
private:
	Point* points;

	void copyFrom(const ModifiableIntegersFunction& other);
	void moveFrom(ModifiableIntegersFunction&& other);
	void free();
};
ModifiableIntegersFunction operator+(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
ModifiableIntegersFunction operator-(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
