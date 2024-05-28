#pragma once
#include "Pair.hpp"
#include "Vector.hpp"

class BaseFunctionalityClass
{
public:
	virtual const Pair<bool, int32_t>& operator()(int32_t n) const = 0;
	virtual ~BaseFunctionalityClass() = default;
protected:
	Vector<Pair<int32_t, int32_t>> pairsVector;
};