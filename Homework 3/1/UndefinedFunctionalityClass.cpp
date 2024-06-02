#include "UndefinedFunctionalityClass.h"

UndefinedFunctionalityClass::UndefinedFunctionalityClass(const int32_t* undefinedResults, uint16_t N)
{
	for (size_t i = 0; i < N; i++)
	{
		Pair<int32_t, int32_t> newPair(undefinedResults[i], 0);
		pairsVector.pushBack(newPair);
	}

	delete[] undefinedResults;
}

const Pair<bool, int32_t>& UndefinedFunctionalityClass::operator()(int32_t n) const
{
	for (size_t i = 0; i < pairsVector.getSize(); i++)
	{
		if (pairsVector[i].getFirst() == n)
		{
			return Pair<bool, int32_t>(false, 0);
		}
	}

	return Pair<bool, int32_t>(true, n);
}

BaseFunctionalityClass* UndefinedFunctionalityClass::clone() const
{
	return new UndefinedFunctionalityClass(*this);
}
