#pragma once
#include "ExtremesFunctionHolder.h"

class MaxPartialFunction : public ExtremesFunctionHolder
{
public:
	MaxPartialFunction(PartialFunction** functions, uint16_t N);
	int32_t operator()(int32_t n) const override;
	PartialFunction* clone() const override;
private:
};
