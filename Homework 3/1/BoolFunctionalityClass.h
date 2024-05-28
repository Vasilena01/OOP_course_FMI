#pragma once
#include "BaseFunctionalityClass.h"

class BoolFunctionalityClass : public BaseFunctionalityClass
{
public:
	BoolFunctionalityClass(const int32_t* arguments, uint16_t N);
	const Pair<bool, int32_t>& operator()(int32_t n) const override;
private:
};