#include <iostream>
#include <fstream>
#include "PartialFunctionFactory.h"
#include "PartialFunctionByCriteria.hpp"
#include "RunProjectClass.h"

int main()
{
	PartialFunction* function = PartialFunctionFactory::createFunction("third.dat");
	RunProjectClass::executeFunc(function);
}