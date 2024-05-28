#pragma once
#include "BaseFunctionalityClass.h"

class UndefinedFunctionalityClass : public BaseFunctionalityClass
{
public:
	UndefinedFunctionalityClass(const int32_t* undefinedResults, uint16_t N);
	const Pair<bool, int32_t>& operator()(int32_t n) const override;
private:
};