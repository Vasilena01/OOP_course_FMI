#include "PartialFunctionByCriteria.h"

PartialFunctionByCriteria::PartialFunctionByCriteria()
{
	functionalityClass = nullptr;
	function = nullptr;
}

PartialFunctionByCriteria::PartialFunctionByCriteria(const BaseFunctionalityClass* functionalityClass)
{
	this->functionalityClass = functionalityClass;
}

PartialFunctionByCriteria::PartialFunctionByCriteria(const Pair<bool, int>& (*function)(int n))
{
	this->function = function;
}

int32_t PartialFunctionByCriteria::operator()(int32_t n) const
{
	if (!function)
		throw std::runtime_error("Function pointer is null.");

	Pair<bool, int> toReturn = function(n);

	if (toReturn.getFirst())
	{
		return toReturn.getSecond();
	}
	else
	{
		throw std::invalid_argument("Function is not defined for this point!");
		return 0;
	}
}

bool PartialFunctionByCriteria::isDefined(int32_t n) const
{
	if (!function)
		throw std::runtime_error("Function pointer is null.");
	else
		return function(n).getFirst() ? true : false;

	return false;
}

PartialFunction* PartialFunctionByCriteria::clone() const
{
	return new PartialFunctionByCriteria(*this);
}
