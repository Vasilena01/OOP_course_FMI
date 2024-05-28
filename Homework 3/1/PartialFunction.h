#pragma once
#include <iostream>

class PartialFunction
{
public:
	virtual int32_t operator()(int32_t n) const = 0;
	virtual bool isDefined(int32_t n) const = 0;
	virtual PartialFunction* clone() const = 0;

	// TODO - da se razpishe
	virtual ~PartialFunction() = default;
private:
};