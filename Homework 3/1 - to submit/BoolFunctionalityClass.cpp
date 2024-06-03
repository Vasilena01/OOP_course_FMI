#include "BoolFunctionalityClass.h"

BoolFunctionalityClass::BoolFunctionalityClass(const int32_t* arguments, uint16_t N)
{
	for (size_t i = 0; i < N; i++)
	{
		valuesVector.pushBack(arguments[i]);
	}

	delete[] arguments;
}

const Pair<bool, int32_t>& BoolFunctionalityClass::operator()(int32_t n) const
{
	for (size_t i = 0; i < valuesVector.getSize(); i++)
	{
		if (valuesVector[i] == n)
		{
			return Pair<bool, int32_t>(true, 1);
		}
	}

	return Pair<bool, int32_t>(true, 0);
}

BaseFunctionalityClassWithoutPairs* BoolFunctionalityClass::clone() const
{
	return new BoolFunctionalityClass(*this);
}
