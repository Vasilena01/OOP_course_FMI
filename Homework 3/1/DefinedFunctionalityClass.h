#pragma once
#include "BaseFunctionalityClass.h"

class DefinedFunctionalityClass : public BaseFunctionalityClass
{
public:
	DefinedFunctionalityClass() = default;
	DefinedFunctionalityClass(const int32_t* arguments, const int32_t* results, uint16_t N);

	const Pair<bool, int32_t>& operator()(int32_t n) const override;
	BaseFunctionalityClass* clone() const override;
private:
};
