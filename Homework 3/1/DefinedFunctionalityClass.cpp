#include "DefinedFunctionalityClass.h"

DefinedFunctionalityClass::DefinedFunctionalityClass(const int32_t* arguments, const int32_t* results, uint16_t N)
{
	for (size_t i = 0; i < N; i++)
	{
		Pair<int32_t, int32_t> newPair(arguments[i], results[i]);
		pairsVector.pushBack(newPair);
	}

	delete[] arguments;
	delete[] results;
}

const Pair<bool, int32_t>& DefinedFunctionalityClass::operator()(int32_t n) const
{
	for (size_t i = 0; i < pairsVector.getSize(); i++)
	{
		if (pairsVector[i].getFirst() == n)
			return Pair<bool, int32_t>(true, pairsVector[i].getSecond());
	}

	return Pair<bool, int32_t>(false, 0);
}
