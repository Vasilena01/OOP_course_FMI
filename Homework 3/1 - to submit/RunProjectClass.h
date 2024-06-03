#pragma once
#include "PartialFunction.h"

class RunProjectClass
{
public:
	static void executeFunc(PartialFunction*& function);
private:
	static void funcMode1(PartialFunction*& function);
	static void funcMode2(PartialFunction*& function);
};

