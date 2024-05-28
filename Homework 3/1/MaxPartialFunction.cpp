#include "MaxPartialFunction.h"

MaxPartialFunction::MaxPartialFunction(PartialFunction** functions, uint16_t N) : ExtremesFunctionHolder(functions, N)
{}

int32_t MaxPartialFunction::operator()(int32_t n) const
{
	if (!isDefined(n))
		throw std::logic_error("Function is not defined for n!");

	uint32_t maxValue = functionsCollection[0]->operator()(n);
	for (size_t i = 1; i < functionsCollection.getSize(); i++)
	{
		uint32_t currValue = functionsCollection[i]->operator()(n);

		if (currValue > maxValue)
			maxValue = currValue;
	}

	return maxValue;
}

PartialFunction* MaxPartialFunction::clone() const
{
	return new MaxPartialFunction(*this);
}
