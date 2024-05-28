#include "MinPartialFunction.h"

MinPartialFunction::MinPartialFunction(PartialFunction** functions, uint16_t N) : ExtremesFunctionHolder(functions, N)
{
}

int32_t MinPartialFunction::operator()(int32_t n) const
{
	if (!isDefined(n))
		throw std::logic_error("Function is not defined for n!");

	uint32_t minValue = functionsCollection[0]->operator()(n);
	for (size_t i = 1; i < functionsCollection.getSize(); i++)
	{
		uint32_t currValue = functionsCollection[i]->operator()(n);

		if (currValue < minValue)
			minValue = currValue;
	}

	return minValue;
}

PartialFunction* MinPartialFunction::clone() const
{
	return new MinPartialFunction(*this);
}
