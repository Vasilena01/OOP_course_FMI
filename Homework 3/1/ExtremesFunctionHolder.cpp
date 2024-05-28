#include "ExtremesFunctionHolder.h"

ExtremesFunctionHolder::ExtremesFunctionHolder(PartialFunction** functions, uint16_t N)
{
	for (size_t i = 0; i < N; i++)
	{
		functionsCollection.addFunction(functions[i]);
	}
}

bool ExtremesFunctionHolder::isDefined(int32_t n) const
{
	for (size_t i = 0; i < functionsCollection.getSize(); i++)
	{
		if (!functionsCollection[i]->isDefined(n))
			return false;
	}

	return true;
}
