#pragma once
#include "BaseFunctionalityClassWithoutPairs.h"

class BoolFunctionalityClass : public BaseFunctionalityClassWithoutPairs
{
public:
	BoolFunctionalityClass() = default;
	BoolFunctionalityClass(const int32_t* arguments, uint16_t N);
	const Pair<bool, int32_t>& operator()(int32_t n) const override;
	BaseFunctionalityClassWithoutPairs* clone() const override;
private:
};