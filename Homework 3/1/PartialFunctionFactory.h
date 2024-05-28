#pragma once
#include "PartialFunction.h"
#include "BaseFunctionalityClass.h"

class PartialFunctionFactory
{
public:
	static PartialFunction* createFunction(const char* fileName);
private:
	static PartialFunction* createFunctionByType(uint16_t N, uint16_t T, std::ifstream& file);
	static PartialFunction* createFunctionByCriteria(const BaseFunctionalityClass* obj);
	static PartialFunction* createMaxFunction(PartialFunction** functions, uint16_t N);
	static PartialFunction* createMinFunction(PartialFunction** functions, uint16_t N);
};