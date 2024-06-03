#pragma once
#include "BaseFunctionalityClassWithoutPairs.h"

class UndefinedFunctionalityClass : public BaseFunctionalityClassWithoutPairs
{
public:
	UndefinedFunctionalityClass() = default;
	UndefinedFunctionalityClass(const int32_t* undefinedResults, uint16_t N);

	const Pair<bool, int32_t>& operator()(int32_t n) const override;
	BaseFunctionalityClassWithoutPairs* clone() const override;
private:
};