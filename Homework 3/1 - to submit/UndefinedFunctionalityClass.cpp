#include "UndefinedFunctionalityClass.h"

UndefinedFunctionalityClass::UndefinedFunctionalityClass(const int32_t* undefinedResults, uint16_t N)
{
	for (size_t i = 0; i < N; i++)
	{
		valuesVector.pushBack(undefinedResults[i]);
	}

	delete[] undefinedResults;
}

const Pair<bool, int32_t>& UndefinedFunctionalityClass::operator()(int32_t n) const
{
	for (size_t i = 0; i < valuesVector.getSize(); i++)
	{
		if (valuesVector[i] == n)
		{
			return Pair<bool, int32_t>(false, 0);
		}
	}

	return Pair<bool, int32_t>(true, n);
}

BaseFunctionalityClassWithoutPairs* UndefinedFunctionalityClass::clone() const
{
	return new UndefinedFunctionalityClass(*this);
}
