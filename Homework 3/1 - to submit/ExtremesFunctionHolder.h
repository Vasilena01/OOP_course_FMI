#pragma once
#include "FunctionsCollection.h"

class ExtremesFunctionHolder : public PartialFunction
{
public:
	ExtremesFunctionHolder(PartialFunction** functions, uint16_t N);

	int32_t operator()(int32_t n) const = 0;
	bool isDefined(int32_t n) const final;
	PartialFunction* clone() const = 0;
protected:
	FunctionsCollection functionsCollection;
};

