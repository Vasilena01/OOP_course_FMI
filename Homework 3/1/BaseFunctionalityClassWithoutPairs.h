#pragma once
#include "Pair.hpp"
#include "Vector.hpp"

class BaseFunctionalityClassWithoutPairs
{
public:
	virtual const Pair<bool, int32_t>& operator()(int32_t n) const = 0;

	virtual BaseFunctionalityClassWithoutPairs* clone() const = 0;

	virtual ~BaseFunctionalityClassWithoutPairs() = default;
protected:
	Vector<int32_t> valuesVector;
};