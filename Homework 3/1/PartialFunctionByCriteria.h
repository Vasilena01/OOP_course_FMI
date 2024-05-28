#pragma once
#include "PartialFunction.h"
#include "BaseFunctionalityClass.h"

class PartialFunctionByCriteria : public PartialFunction
{
public:
	PartialFunctionByCriteria();
	PartialFunctionByCriteria(const BaseFunctionalityClass* functionalityClass);
	PartialFunctionByCriteria(const Pair<bool, int>& (*function)(int n));

	int32_t operator()(int32_t n) const override;
	bool isDefined(int32_t n) const override;
	PartialFunction* clone() const override;
private:

	const BaseFunctionalityClass* functionalityClass;
	const Pair<bool, int>& (*function)(int n);
};