#include "BoolFunctionalityClass.h"

BoolFunctionalityClass::BoolFunctionalityClass(const int32_t* arguments, uint16_t N)
{
	for (size_t i = 0; i < N; i++)
	{
		Pair<int32_t, int32_t> newPair(arguments[i], 1);
		pairsVector.pushBack(newPair);
	}

	delete[] arguments;
}

const Pair<bool, int32_t>& BoolFunctionalityClass::operator()(int32_t n) const
{
	for (size_t i = 0; i < pairsVector.getSize(); i++)
	{
		if (pairsVector[i].getFirst() == n)
		{
			return Pair<bool, int32_t>(true, 1);
		}
	}

	return Pair<bool, int32_t>(true, 0);
}

BaseFunctionalityClass* BoolFunctionalityClass::clone() const
{
	return new BoolFunctionalityClass(*this);
}
