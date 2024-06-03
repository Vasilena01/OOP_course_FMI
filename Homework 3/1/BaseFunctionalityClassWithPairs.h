#pragma once
#include "Pair.hpp"
#include "Vector.hpp"

class BaseFunctionalityClassWithPairs
{
public:
	virtual const Pair<bool, int32_t>& operator()(int32_t n) const = 0;

	virtual BaseFunctionalityClassWithPairs* clone() const = 0;

	virtual ~BaseFunctionalityClassWithPairs() = default;
protected:
	Vector<Pair<int32_t, int32_t>> pairsVector;
};

