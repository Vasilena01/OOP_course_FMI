#pragma once
#include "PartialFunction.h";
#include "DefinedFunctionalityClass.h";
#include "UndefinedFunctionalityClass.h";
#include "BoolFunctionalityClass.h";

template <typename T>
class PartialFunctionByCriteria : public PartialFunction {
public:
	PartialFunctionByCriteria(const T& function);

	int32_t operator()(int32_t n) const override;
	bool isDefined(int32_t n) const override;
	PartialFunction* clone() const override;
private:
	T function;
};

template<typename T>
PartialFunctionByCriteria<T>::PartialFunctionByCriteria(const T& function)
{
	this->function = function;
}

template<typename T>
int32_t PartialFunctionByCriteria<T>::operator()(int32_t n) const
{
	Pair<bool, int32_t> value = function(n);

	if (!value.getFirst())
		throw std::invalid_argument("Function is not defined for this point!");

	return value.getSecond();
}

template<typename T>
bool PartialFunctionByCriteria<T>::isDefined(int32_t n) const
{
	return function(n).getFirst() ? true : false;
}

template<typename T>
PartialFunction* PartialFunctionByCriteria<T>::clone() const
{
	return new PartialFunctionByCriteria(*this);
}