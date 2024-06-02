#pragma once
#include "BaseFunctionalityClass.h"

class UndefinedFunctionalityClass : public BaseFunctionalityClass
{
public:
	UndefinedFunctionalityClass() = default;
	UndefinedFunctionalityClass(const int32_t* undefinedResults, uint16_t N);

	const Pair<bool, int32_t>& operator()(int32_t n) const override;
	BaseFunctionalityClass* clone() const override;
private:
};